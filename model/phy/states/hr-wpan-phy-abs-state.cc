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

#include "hr-wpan-phy-abs-state.h"
#include <ns3/hr-wpan-phy.h>
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanPhyAbsState");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhyAbsState);

	HrWpanPhyAbsState::HrWpanPhyAbsState(Ptr<HrWpanPhy> hrWpanPhy) :
		m_hrWpanPhy(hrWpanPhy)
	{
		NS_LOG_FUNCTION(this);
	}

	void HrWpanPhyAbsState::EndRx(Ptr<SpectrumSignalParameters> params) 
	{
		NS_LOG_FUNCTION(this << params);
	}

	void HrWpanPhyAbsState::EndTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}

	void HrWpanPhyAbsState::StartTx(Ptr<HrWpanSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}

	void HrWpanPhyAbsState::StartRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}

}