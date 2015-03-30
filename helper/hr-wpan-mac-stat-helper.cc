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

#include "hr-wpan-mac-stat-helper.h"
#include <ns3/config.h>
#include <ns3/callback.h>
#include <ns3/hr-wpan-timestamp-tag.h>
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanMacStatHelper");

	namespace HrWpan
	{

		MacStatHelper::MacStatHelper()
		{
			reset();
		}

		void MacStatHelper::attach()
		{
			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/MacRx",
				MakeCallback(&MacStatHelper::incRx, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/MacTx",
				MakeCallback(&MacStatHelper::incTx, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/Queue/Drop",
				MakeCallback(&MacStatHelper::incQueueDrop, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/Queue/$ns3::Queue/Enqueue",
				MakeCallback(&MacStatHelper::incQueueIn, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/Queue/$ns3::Queue/Dequeue",
				MakeCallback(&MacStatHelper::incQueueOut, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Mac/Queue/Reinsert",
				MakeCallback(&MacStatHelper::incQueueReIn, this));
		}

		void MacStatHelper::reset()
		{
			m_tx = 0;
			m_rx = 0;
			m_queueDrop = 0;
			m_queueIn = 0;
			m_queueOut = 0;
			m_queueReIn = 0;
			m_totalDelay = Seconds(0);

		}

		void MacStatHelper::incRx(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);
			++m_rx;

			TimestampTag timestampTag;
			bool pickedUp = p->PeekPacketTag(timestampTag);
			
			if (pickedUp)
			{
				Time start = timestampTag.GetTimestamp();
				Time end = Simulator::Now();

				Time delay = end - start;

				m_totalDelay += delay;

			}

		}

		void MacStatHelper::incTx(std::string str, Ptr<const Packet> p)
		{
			++m_tx;

		}

		uint32_t MacStatHelper::getRx() const
		{
			return m_rx;
		}

		uint32_t MacStatHelper::getTx() const
		{
			return m_tx;
		}

		uint32_t MacStatHelper::getQueueDrop() const
		{
			return m_queueDrop;
		}

		uint32_t MacStatHelper::getQueueIn() const
		{
			return m_queueIn;
		}

		uint32_t MacStatHelper::getQueueReIn() const
		{
			return m_queueReIn;
		}

		uint32_t MacStatHelper::getQueueOut() const
		{
			NS_LOG_FUNCTION(this);
			return m_queueOut;
		}

		void MacStatHelper::incQueueDrop(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);
			++m_queueDrop;
		}

		void MacStatHelper::incQueueIn(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);
			++m_queueIn;
		}

		void MacStatHelper::incQueueReIn(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);
			++m_queueReIn;
		}


		void MacStatHelper::incQueueOut(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);
			++m_queueOut;
		}

		Time MacStatHelper::getTotalDelay() const
		{
			NS_LOG_FUNCTION(this);
			return m_totalDelay;
		}

		Time MacStatHelper::getAvgDelay() const
		{
			NS_LOG_FUNCTION(this);
			if (getRx() == 0){
				return Seconds(0);
			}
			return m_totalDelay / double(getRx());
		}

	} //namespace HrWpan

} // namespace ns3