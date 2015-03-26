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
* Author:
*	Igor Di Paolo <igor.di.paolo@gmail.com>
*/


#include "hr-wpan-mac-slotted-aloha-sync.h"
#include <ns3/nstime.h>
#include <ns3/log.h>

namespace ns3
{
	namespace HrWpan
	{

		TypeId MacSlottedAlohaSync::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpan::MacSlottedAlohaSync").
				SetParent<MacManagerSync>().
				AddConstructor<MacSlottedAlohaSync>()//.
				
				;
				
			return tid;
		}

		MacSlottedAlohaSync::MacSlottedAlohaSync()
		{
			m_startTime = Seconds(1.0);
			m_endTime = Seconds(10.0);
			m_timeSlot = MilliSeconds(1.0);
		}

		void MacSlottedAlohaSync::Activate()
		{
			m_timeSlotNumber = 0;
			Simulator::Schedule(m_startTime, &MacSlottedAlohaSync::nextSlot, this);
		}

		void MacSlottedAlohaSync::nextSlot()
		{
			std::list< MacManagerListener * >::iterator i = m_listeners.begin();
			Time nextTrigger = m_startTime + (m_timeSlot*m_timeSlotNumber);

			while (i != m_listeners.end())
			{

				(*i)->SendPkt(m_timeSlot);
				++i;
			}

			m_timeSlotNumber++;

			

			if (nextTrigger < m_endTime)
			{
				Simulator::Schedule(m_timeSlot, &MacSlottedAlohaSync::nextSlot, this);
			}

		}

	} // namespace HrWpan

} // namespace ns3
