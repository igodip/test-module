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

#include "hr-wpan-phy-tx-on-state.h"
#include <ns3/hr-wpan-phy.h>

namespace ns3
{
	HrWpanPhyTxOnState::HrWpanPhyTxOnState(Ptr<HrWpanPhy> hrWpanPhy) :
		HrWpanPhyAbsState(hrWpanPhy)
	{

	}


	void HrWpanPhyTxOnState::StartRx(Ptr<SpectrumSignalParameters> params){

	}


	void HrWpanPhyTxOnState::EndRx(Ptr<SpectrumSignalParameters> params){

	}


	void HrWpanPhyTxOnState::StartTx(Ptr<HrWpanSpectrumSignalParameters> params){

	}


	void HrWpanPhyTxOnState::EndTx(Ptr<HrWpanSpectrumSignalParameters> params){


	}
}


