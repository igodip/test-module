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

#ifndef HR_WPAN_DEVID_HELPER_H
#define HR_WPAN_DEVID_HELPER_H

#include <ns3/net-device-container.h>
#include <ns3/mac48-address.h>
#include <ns3/hr-wpan-dev-id.h>
#include <map>

namespace ns3
{
	namespace HrWpan
	{
		class DevIdHelper
		{
		public:

			static  DevIdHelper & GetInstance();
			
			void Install(NetDeviceContainer ndc);

			DevId GetDevIdByMac(const Mac48Address &  mac) const;
			Mac48Address GetMacByDevId(const DevId & devId) const;

		protected:
			
			DevIdHelper();

		private:
			
			std::map<DevId, Mac48Address> m_devIdToMac;
			std::map<Mac48Address, DevId> m_macToDevId;

		}; // DevIdHelper

	} // namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_DEVID_HELPER_H_