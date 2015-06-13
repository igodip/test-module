/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2015 KTH
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation;
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Author:
*	Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-channel.h"

#include <ns3/spectrum-channel.h>
#include <ns3/spectrum-phy.h>
#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/assert.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/antenna-model.h>
#include <ns3/propagation-delay-model.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/spectrum-propagation-loss-model.h>
#include <ns3/net-device.h>
#include <ns3/node.h>
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-sector-antenna.h>
#include <ns3/hr-wpan-net-device.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpanChannel");

	namespace HrWpan
	{

		NS_OBJECT_ENSURE_REGISTERED(HrWpanChannel);

		TypeId HrWpanChannel::GetTypeId(void)
		{
			NS_LOG_FUNCTION_NOARGS();
			static TypeId tid = TypeId("ns3::HrWpan::Channel")
				.SetParent<SingleModelSpectrumChannel>();
			return tid;
		}

		void HrWpanChannel::StartTx(Ptr<SpectrumSignalParameters> txParams)
		{
			NS_LOG_FUNCTION(this << txParams->psd << txParams->duration << txParams->txPhy);
			NS_ASSERT_MSG(txParams->psd, "NULL txPsd");
			NS_ASSERT_MSG(txParams->txPhy, "NULL txPhy");

			// just a sanity check routine. We might want to remove it to save some computational load -- one "if" statement  ;-)
			if (m_spectrumModel == 0)
			{
				// first pak, record SpectrumModel
				m_spectrumModel = txParams->psd->GetSpectrumModel();
			}
			else
			{
				// all attached SpectrumPhy instances must use the same SpectrumModel
				NS_ASSERT(*(txParams->psd->GetSpectrumModel()) == *m_spectrumModel);
			}

			NS_LOG_INFO("Computing the receivers");

			TopologyAggregator aggregator = TopologyAggregator::getInstance();
			Ptr<SectorAntenna> senAntenna = DynamicCast< SectorAntenna >(txParams->txAntenna);
			std::set<Ptr<Node> > receivers = aggregator.GetSteeredReceivers(senAntenna->GetOrientation());

			NS_LOG_INFO(receivers.size());
			
			Ptr<MobilityModel> senderMobility = txParams->txPhy->GetMobility();

			for (std::set<Ptr<Node> >::const_iterator start_rx = receivers.begin(); start_rx != receivers.end();
				++start_rx)
			{

				Ptr<HrWpanNetDevice> receiverDev = DynamicCast<HrWpanNetDevice>((*start_rx)->GetDevice(0));
				Ptr<SpectrumPhy> phy = receiverDev->GetPhy();

				if ( phy != txParams->txPhy)
				{
					Time delay = MicroSeconds(0);

					Ptr<MobilityModel> receiverMobility = phy->GetMobility();
					NS_LOG_LOGIC("copying signal parameters " << txParams);
					Ptr<SpectrumSignalParameters> rxParams = txParams->Copy();

					if (senderMobility && receiverMobility)
					{
						double pathLossDb = 0;
						if (rxParams->txAntenna != 0)
						{
							Angles txAngles(receiverMobility->GetPosition(), senderMobility->GetPosition());
							double txAntennaGain = rxParams->txAntenna->GetGainDb(txAngles);
							NS_LOG_LOGIC("txAntennaGain = " << txAntennaGain << " dB");
							pathLossDb -= txAntennaGain;
						}
						Ptr<AntennaModel> rxAntenna = phy->GetRxAntenna();
						if (rxAntenna != 0)
						{
							Angles rxAngles(senderMobility->GetPosition(), receiverMobility->GetPosition());
							double rxAntennaGain = rxAntenna->GetGainDb(rxAngles);
							NS_LOG_LOGIC("rxAntennaGain = " << rxAntennaGain << " dB");
							pathLossDb -= rxAntennaGain;
						}
						if (m_propagationLoss)
						{
							double propagationGainDb = m_propagationLoss->CalcRxPower(0, senderMobility, receiverMobility);
							NS_LOG_LOGIC("propagationGainDb = " << propagationGainDb << " dB");
							pathLossDb -= propagationGainDb;
						}
						NS_LOG_LOGIC("total pathLoss = " << pathLossDb << " dB");
						m_pathLossTrace(txParams->txPhy, phy, pathLossDb);
						if (pathLossDb > m_maxLossDb)
						{
							// beyond range
							continue;
						}
						double pathGainLinear = std::pow(10.0, (-pathLossDb) / 10.0);
						*(rxParams->psd) *= pathGainLinear;

						if (m_spectrumPropagationLoss)
						{
							rxParams->psd = m_spectrumPropagationLoss->CalcRxPowerSpectralDensity(rxParams->psd, senderMobility, receiverMobility);
						}

						if (m_propagationDelay)
						{
							delay = m_propagationDelay->GetDelay(senderMobility, receiverMobility);
						}
					}


					Ptr<NetDevice> netDev = phy->GetDevice();
					if (netDev)
					{
						// the receiver has a NetDevice, so we expect that it is attached to a Node
						uint32_t dstNode = netDev->GetNode()->GetId();
						Simulator::ScheduleWithContext(dstNode, delay, &HrWpanChannel::StartRx, this, rxParams, phy);
					}
					else
					{
						// the receiver is not attached to a NetDevice, so we cannot assume that it is attached to a node
						Simulator::Schedule(delay, &HrWpanChannel::StartRx, this,
							rxParams, phy);
					}
				}
			}
		}
	} // namespace HrWpan

} // namespace ns3