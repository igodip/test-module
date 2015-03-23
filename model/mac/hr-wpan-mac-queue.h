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

#ifndef HR_WPAN_MAC_QUEUE_H
#define HR_WPAN_MAC_QUEUE_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-mac-header.h>
#include <ns3/nstime.h>
#include <ns3/queue.h>

#include <list>

namespace ns3
{
	namespace HrWpan
	{

		class MacQueue : public Queue
		{

		public:

			MacQueue();
			virtual ~MacQueue();

			static TypeId GetTypeId(void);

		protected:
			
			virtual bool DoEnqueue(Ptr<Packet> p);
			virtual Ptr<Packet> DoDequeue(void) ;
			virtual Ptr<const Packet> DoPeek(void) const ;

		private:

			std::list<Ptr<Packet > > m_packets;

		};

	}// namespace HrWpan
	
} //namespace ns3

#endif //HR_WPAN_MAC_QUEUE_H