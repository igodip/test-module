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

		/**
		 * \fn	virtual void HrWpanPhyUser::ReceivePhyPdu(Ptr<Packet> p) = 0;
		 *
		 * \brief	Receive phy PDU.
		 *
		 * \param	p	The Ptr&lt;Packet&gt; to process.
		 */

		virtual void ReceivePhyPdu(Ptr<Packet> p) = 0;

		/**
		 * \fn	virtual void HrWpanPhyUser::ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> msg) = 0;
		 *
		 * \brief	Receive phy control message.
		 *
		 * \param	msg	The message.
		 */

		virtual void ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> msg) = 0;

	};
}

#endif