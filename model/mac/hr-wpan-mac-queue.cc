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

#include "hr-wpan-mac-queue.h"
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanMacQueue");

	namespace HrWpan
	{

		NS_OBJECT_ENSURE_REGISTERED(MacQueue);

		MacQueue::MacQueue()
		{
			NS_LOG_FUNCTION(this);
		}

		MacQueue::~MacQueue()
		{
			NS_LOG_FUNCTION(this);
		}

		TypeId MacQueue::GetTypeId(void)
		{
			NS_LOG_FUNCTION_NOARGS();

			static TypeId tid = TypeId("ns3::HrWpan::MacQueue").
				SetParent<Queue>().
				AddConstructor<MacQueue>()
				.AddTraceSource("Reinsert", "Renqueue a packet in the queue.",
				MakeTraceSourceAccessor(&MacQueue::m_traceReinsert),
				"ns3::Packet::TracedCallback");
			
			return tid;

		}

		bool MacQueue::DoEnqueue(Ptr<Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_packets.push_back(p);

			return true;

		}

		Ptr<Packet> MacQueue::DoDequeue(void)
		{
			NS_LOG_FUNCTION(this);

			if (m_packets.size() == 0)
			{
				return NULL;
			}

			Ptr<Packet> packet = m_packets.front();
			m_packets.pop_front();

			return packet;
		}

		Ptr<const Packet> MacQueue::DoPeek(void) const
		{
			NS_LOG_FUNCTION(this);

			if (m_packets.size() == 0)
			{
				return NULL;
			}

			return m_packets.front();
		}

		bool MacQueue::PushFront(Ptr<Packet> p)
		{
			m_packets.push_front(p);
			m_traceReinsert(p);

			uint32_t size = p->GetSize();
			m_nBytes += size;
			m_nTotalReceivedBytes += size;

			m_nPackets++;
			m_nTotalReceivedPackets++;
			return true;
		}


	}

}

