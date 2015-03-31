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
#include "hr-wpan-devid-helper.h"

#include <ns3/hr-wpan-dev-id.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/ipv4-address-helper.h>
#include <ns3/log.h>

namespace ns3
{
	namespace HrWpan
	{

		NS_LOG_COMPONENT_DEFINE("HrWpanDevIDHelper");

		DevIdHelper::DevIdHelper()
		{
			NS_LOG_FUNCTION(this);

			//Populate with broadcast
			
			m_devIdToMac[DevId::GetBroadcast()] = Mac48Address::GetBroadcast();
			m_macToDevId[Mac48Address::GetBroadcast()] = DevId::GetBroadcast();

		}

		void DevIdHelper::Install(NetDeviceContainer ndc)
		{
			NS_LOG_FUNCTION(this);

			for (NetDeviceContainer::Iterator i = ndc.Begin(); i != ndc.End(); ++i)
			{
				
				Ptr<HrWpan::HrWpanNetDevice> netDevice = DynamicCast<HrWpan::HrWpanNetDevice>(*i);
				
				DevId devId = DevId::Allocate();

				netDevice->GetMac()->SetDevId(devId);

				//populate
				m_devIdToMac[devId] = netDevice->GetMac()->GetAddress();
				m_macToDevId[netDevice->GetMac()->GetAddress()] = devId;
				
			}
		}


		DevIdHelper & DevIdHelper::GetInstance()
		{
			static DevIdHelper devIdHelper;
			return devIdHelper;
		}

		DevId DevIdHelper::GetDevIdByMac(const Mac48Address & mac) const
		{
			NS_LOG_FUNCTION(this << mac);
			return m_macToDevId.at(mac);

		}

		Mac48Address DevIdHelper::GetMacByDevId(const DevId & devId) const
		{
			NS_LOG_FUNCTION(this << devId);
			NS_LOG_INFO(m_devIdToMac.size());
			return m_devIdToMac.at(devId);

		}

	} //namespace HrWpan

} // namespace ns3