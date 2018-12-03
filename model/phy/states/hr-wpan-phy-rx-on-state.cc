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

#include "hr-wpan-phy-rx-on-state.h"

#include <ns3/hr-wpan-phy.h>
#include <ns3/log.h>
#include <ns3/simulator.h>

#include <ns3/hr-wpan-spectrum-value-helper.h>
#include <ns3/spectrum-value.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanPhyRxOnState");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhyRxOnState);

	HrWpanPhyRxOnState::HrWpanPhyRxOnState(Ptr<HrWpanPhy> wpanPhy) :
		HrWpanPhyAbsState(wpanPhy)
	{
		NS_LOG_FUNCTION(this << wpanPhy);
	}

	void HrWpanPhyRxOnState::StartRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
		
		HrWpanSpectrumSignalParameters psdHelper;

		Ptr<HrWpanSpectrumSignalParameters> hrWpanRxParams = DynamicCast<HrWpanSpectrumSignalParameters>(params);

		// It isn't an our packet
		if (hrWpanRxParams == 0)
		{
			Simulator::Schedule(params->duration, &HrWpanPhy::EndRx, m_hrWpanPhy->GetPointer(), params);
			return;
		}

		Ptr<Packet> p = (hrWpanRxParams->packetBurst->GetPackets()).front();
		m_hrWpanPhy->m_currentPacket = hrWpanRxParams;

		NS_ASSERT(p != 0);
		m_hrWpanPhy->m_phyRxBeginTrace(p);

		m_hrWpanPhy->m_currentState = m_hrWpanPhy->m_stateFactory->GetRxBusyState();
		m_hrWpanPhy->m_receiveOn = Simulator::Schedule(hrWpanRxParams->duration, &HrWpanPhy::EndRx, m_hrWpanPhy->GetPointer(), hrWpanRxParams);
		
	}

	void HrWpanPhyRxOnState::EndRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Rx not started yet!");
	}

	void HrWpanPhyRxOnState::StartTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Rx On Mode can't Tx");
	}

	void HrWpanPhyRxOnState::EndTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Rx On Mode can't Tx");
	}

}//Namespace ns3
