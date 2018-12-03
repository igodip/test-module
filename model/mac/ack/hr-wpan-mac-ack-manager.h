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

#ifndef HR_WPAN_MAC_ACK_MANAGER_H
#define HR_WPAN_MAC_ACK_MANAGER_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/simulator.h>
#include <map>

namespace ns3
{
	class HrWpanMac;

	namespace HrWpan
	{
		class MacAckManager :public Object
		{

		public:
			
			MacAckManager();

			static TypeId GetTypeId();
			
			void AddPacket(Ptr<Packet> packet);


		protected:

			void ackExpired(Ptr<Packet> packet);

			std::map<Ptr<Packet>, EventId> m_packetEvent;
			
			Ptr<HrWpanMac> m_mac;

			static Time m_maxWaitAck;

		};
	}
}

#endif