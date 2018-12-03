/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
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
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-phy-rx-busy-state.h"

#include <ns3/hr-wpan-phy.h>
#include <ns3/hr-wpan-spectrum-value-helper.h>
#include <ns3/spectrum-value.h>
#include <ns3/simulator.h>
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanPhyRxBusyState");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhyRxBusyState);

	HrWpanPhyRxBusyState::HrWpanPhyRxBusyState(Ptr<HrWpanPhy> hrWpanPhy) :
		HrWpanPhyAbsState(hrWpanPhy)
	{
		NS_LOG_FUNCTION(this << hrWpanPhy);
	}

	void HrWpanPhyRxBusyState::StartRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
		NS_LOG_WARN("Collision");

		//Remove schedule
		if (m_hrWpanPhy->m_receiveOn.IsRunning())
		{
			Simulator::Remove(m_hrWpanPhy->m_receiveOn);
		}

		m_hrWpanPhy->m_phyRxDropTrace(m_hrWpanPhy->m_currentPacket->packetBurst->GetPackets().front());

		m_hrWpanPhy->m_currentPacket = 0;
		m_hrWpanPhy->m_currentState = m_hrWpanPhy->m_stateFactory->GetRxOnState();
	}

	void HrWpanPhyRxBusyState::EndRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		Ptr<HrWpanSpectrumSignalParameters> hrWpanParams = DynamicCast<HrWpanSpectrumSignalParameters>(params);

		if (hrWpanParams != 0)
		{
			Ptr<Packet> packet = (hrWpanParams->packetBurst->GetPackets()).front();
			((HrWpanPhyUser *) (m_hrWpanPhy->GetPhyUser()))->ReceivePhyPdu(packet);

			m_hrWpanPhy->m_phyRxEndTrace(packet);
		}


		m_hrWpanPhy->m_currentPacket = 0;
		m_hrWpanPhy->m_currentState = m_hrWpanPhy->m_stateFactory->GetRxOnState();

	}

	void HrWpanPhyRxBusyState::StartTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Tx not allowed!");
	}

	void HrWpanPhyRxBusyState::EndTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Tx not allowed!");
	}


}//namespace ns3