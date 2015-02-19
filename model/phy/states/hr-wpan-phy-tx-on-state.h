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

#ifndef HR_WPAN_PHY_TX_ON_STATE_H
#define HR_WPAN_PHY_TX_ON_STATE_H

#include "hr-wpan-phy-abs-state.h"


namespace ns3
{

	class HrWpanPhyTxOnState : public HrWpanPhyAbsState
	{

	
public:
		HrWpanPhyTxOnState(Ptr<HrWpanPhy> hrWpanPhy);
		virtual void StartRx(Ptr<SpectrumSignalParameters> params);
		virtual void EndRx(Ptr<SpectrumSignalParameters> params);
		virtual void StartTx(Ptr<HrWpanSpectrumSignalParameters> params);
		virtual void EndTx(Ptr<HrWpanSpectrumSignalParameters> params);
};

}
#endif