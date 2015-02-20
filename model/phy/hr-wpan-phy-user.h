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

#ifndef HR_WPAN_PHY_USER_H
#define HR_WPAN_PHY_USER_H

#include <ns3/packet.h>
#include <ns3/hr-wpan-phy-control-message.h>

namespace ns3
{
	class HrWpanPhyUser {

	public:

		virtual void ReceivePhyPdu(Ptr<Packet> p) = 0;

		virtual void ReceiveLteControlMessage(Ptr<HrWpanPhyControlMessage> msg) = 0;
		//Preamble
	};
}

#endif