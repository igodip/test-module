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

#include "hr-wpan-phy-tx-busy-state.h"
#include <ns3/hr-wpan-phy.h>
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanPhyTxBusyState");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhyTxBusyState);

	HrWpanPhyTxBusyState::HrWpanPhyTxBusyState(Ptr<HrWpanPhy> wpanPhy) :
		HrWpanPhyAbsState(wpanPhy)
	{
		NS_LOG_FUNCTION(this << wpanPhy);
	}


	void HrWpanPhyTxBusyState::StartTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		NS_LOG_WARN("Tx On can't transmit another packet");

	}


	void HrWpanPhyTxBusyState::StartRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}


	void HrWpanPhyTxBusyState::EndRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}


	void HrWpanPhyTxBusyState::EndTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		m_hrWpanPhy->m_phyTxEndTrace(params->packetBurst->GetPackets().front());
		m_hrWpanPhy->m_currentState = m_hrWpanPhy->m_stateFactory->GetTxOnState();
	}
}


