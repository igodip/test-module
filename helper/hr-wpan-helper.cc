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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-helper.h"

#include <ns3/single-model-spectrum-channel.h>
#include <ns3/multi-model-spectrum-channel.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/ptr.h>
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanHelper");

	namespace HrWpan {
		
		//NS_OBJECT_ENSURE_REGISTERED(HrWpanHelper);

		HrWpanHelper::HrWpanHelper(void) {
			NS_LOG_FUNCTION(this);

			m_channel = CreateObject<SingleModelSpectrumChannel>();

			Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();
			m_channel->AddPropagationLossModel(lossModel);

			Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();
			m_channel->SetPropagationDelayModel(delayModel);
		}

		HrWpanHelper::HrWpanHelper(bool useMultiModelSpectrumChannel)
		{
			NS_LOG_FUNCTION(this);

			if (useMultiModelSpectrumChannel)
			{
				m_channel = CreateObject<MultiModelSpectrumChannel>();
			}
			else
			{
				m_channel = CreateObject<SingleModelSpectrumChannel>();
			}
			Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();
			m_channel->AddPropagationLossModel(lossModel);

			Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();
			m_channel->SetPropagationDelayModel(delayModel);
		}

		HrWpanHelper::~HrWpanHelper(void)
		{
			NS_LOG_FUNCTION(this);
			m_channel->Dispose();
			m_channel = 0;
		}

		Ptr<SpectrumChannel> HrWpanHelper::GetChannel(void)
		{
			NS_LOG_FUNCTION(this);
			return m_channel;
		}

		void HrWpanHelper::SetChannel(Ptr<SpectrumChannel> spectrumChannel)
		{
			NS_LOG_FUNCTION(this << spectrumChannel);
			m_channel = spectrumChannel;
		}


		NetDeviceContainer HrWpanHelper::install(NodeContainer c) 
		{

			NS_LOG_FUNCTION(this);

			NetDeviceContainer devices;

			for (NodeContainer::Iterator i = c.Begin(); i != c.End(); i++)
			{

				Ptr<Node> node = *i;

				Ptr<HrWpanNetDevice> netDevice = CreateObject<HrWpanNetDevice>();
				netDevice->SetChannel(m_channel);

				node->AddDevice(netDevice);
				netDevice->SetNode(node);
				// \todo add the capability to change short address, extended
				// address and panId. Right now they are hardcoded in LrWpanMac::LrWpanMac ()
				devices.Add(netDevice);

			}

			return devices;

		}

	} // namespace hrWpan

} // namespace ns3