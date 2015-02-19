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

#include "hr-wpan-phy-state-factory.h"
#include <ns3/hr-wpan-phy.h>

namespace ns3
{
	HrWpanPhyStateFactory::HrWpanPhyStateFactory(Ptr<HrWpanPhy>  hrWpanPhy)
		: m_wpanPhy(hrWpanPhy)
	{
		m_idleState = CreateObject<HrWpanPhyIdleState>(m_wpanPhy);
		m_txOnState = CreateObject<HrWpanPhyTxOnState>(m_wpanPhy);
		m_txBusyState = CreateObject<HrWpanPhyTxBusyState>(m_wpanPhy);
		m_rxBusyState = CreateObject<HrWpanPhyRxBusyState>(m_wpanPhy);
		m_rxOnState = CreateObject<HrWpanPhyRxOnState>(m_wpanPhy);
	}

	Ptr<HrWpanPhyIdleState> HrWpanPhyStateFactory::GetIdleState() const
	{
		return m_idleState;
	}

	Ptr<HrWpanPhyRxOnState> HrWpanPhyStateFactory::GetRxOnState() const
	{
		return m_rxOnState;
	}

	Ptr<HrWpanPhyRxBusyState> HrWpanPhyStateFactory::GetRxBusyState() const
	{
		return m_rxBusyState;
	}

	Ptr<HrWpanPhyTxOnState> HrWpanPhyStateFactory::GetTxOnState() const
	{
		return m_txOnState;
	}

	Ptr<HrWpanPhyTxBusyState> HrWpanPhyStateFactory::GetTxBusyState() const
	{
		return m_txBusyState;
	}
	
}


