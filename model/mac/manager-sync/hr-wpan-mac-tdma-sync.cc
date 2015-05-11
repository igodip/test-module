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


#include "hr-wpan-mac-tdma-sync.h"
#include <ns3/nstime.h>
#include <ns3/log.h>
#include <iostream>


namespace ns3
{
	//NS_LOG_COMPONENT_DEFINE("HrWpanMacTdmaSync");

	namespace HrWpan
	{
		TypeId MacTdmaSync::GetTypeId()
		{

			static TypeId tid = TypeId("ns3::HrWpan::MacTdmaSync").
				SetParent<MacManagerSync>().
				AddConstructor<MacTdmaSync>();

			return tid;
		}

		MacTdmaSync::MacTdmaSync()
		{
			m_startTime = Seconds(0.0);
			m_endTime = Seconds(4.0);
			m_timeSlot = MicroSeconds(800.0);
		}

		void MacTdmaSync::Activate()
		{
			m_current = m_listeners.begin();
			m_timeSlotNumber = 0;
			Simulator::Schedule(m_startTime, &MacTdmaSync::nextDevice,this);
		}

		void MacTdmaSync::nextDevice()
		{
			Time nextTrigger = m_startTime + (m_timeSlot*m_timeSlotNumber);
			(*m_current)->SendPkt(m_timeSlot);
			
			m_current++;
			m_timeSlotNumber++;

			if (m_current == m_listeners.end())
			{
				m_current = m_listeners.begin();
			}

			if (nextTrigger < m_endTime)
			{	
				Simulator::Schedule(m_timeSlot, &MacTdmaSync::nextDevice, this);
			}

		}

	} // namespace HrWpan

} // namespace ns3
