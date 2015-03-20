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

#include "hr-wpan-phy-stat-helper.h"
#include <ns3/config.h>
#include <ns3/callback.h>
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpan::PhyStatHelper");

	namespace HrWpan
	{

		

		PhyStatHelper::PhyStatHelper()
		{
			NS_LOG_FUNCTION(this);

			reset();
		}

		void PhyStatHelper::reset()
		{
			NS_LOG_FUNCTION(this);

			m_txBegin = 0;
			m_rxBegin = 0;
			m_txDrop = 0;
			m_rxDrop = 0;
			m_rxEnd = 0;
			m_txEnd = 0;
		}

		void PhyStatHelper::attach()
		{

			NS_LOG_FUNCTION(this);

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyRxBegin",
				MakeCallback(&PhyStatHelper::incRxBegin, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyRxEnd",
				MakeCallback(&PhyStatHelper::incRxEnd,this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyRxDrop",
				MakeCallback(&PhyStatHelper::incRxDrop, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyTxBegin",
				MakeCallback(&PhyStatHelper::incTxBegin, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyTxDrop",
				MakeCallback(&PhyStatHelper::incTxDrop, this));

			Config::Connect("/NodeList/*/DeviceList/*/$ns3::HrWpan::HrWpanNetDevice/Phy/PhyTxEnd",
				MakeCallback(&PhyStatHelper::incTxEnd, this));
		}

		uint32_t PhyStatHelper::getTxBegin() const
		{
			NS_LOG_FUNCTION(this);

			return m_txBegin;
		}

		uint32_t PhyStatHelper::getRxBegin() const
		{
			NS_LOG_FUNCTION(this);

			return m_rxBegin;
		}

		uint32_t PhyStatHelper::getTxDrop() const
		{
			NS_LOG_FUNCTION(this);

			return m_txDrop;
		}

		uint32_t PhyStatHelper::getRxDrop() const
		{
			NS_LOG_FUNCTION(this);

			return m_rxDrop;
		}

		uint32_t PhyStatHelper::getTxEnd() const
		{
			NS_LOG_FUNCTION(this);

			return m_txEnd;
		}

		uint32_t PhyStatHelper::getRxEnd() const
		{
			NS_LOG_FUNCTION(this);

			return m_rxEnd;
		}

		void PhyStatHelper::incRxBegin(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_rxBegin++;
		}

		void PhyStatHelper::incRxDrop(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_rxDrop++;
		}

		void PhyStatHelper::incRxEnd(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_rxEnd++;
		}

		void PhyStatHelper::incTxBegin(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_txBegin++;
		}

		void PhyStatHelper::incTxDrop(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_txDrop++;
		}

		void PhyStatHelper::incTxEnd(std::string str, Ptr<const Packet> p)
		{
			NS_LOG_FUNCTION(this);

			m_txEnd++;
		}
	}
}