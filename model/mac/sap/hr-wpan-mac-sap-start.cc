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
#include "hr-wpan-mac-sap-start.h"

#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-net-device.h>

namespace ns3
{
	namespace HrWpan
	{

		MacSapUserStart::MacSapUserStart(HrWpanNetDevice * netDevice) :
			MacSapUser(netDevice)
		{

		}

		void MacSapUserStart::Confirm(const MacSapConfirmParams & confirmParams)
		{

		}

		void MacSapUserStart::Indication(const MacSapIndicationParams & indicationParams)
		{

		}

		MacSapProviderStart::MacSapProviderStart(HrWpanMac * mac) :
			MacSapProvider(mac)
		{

		}

		void MacSapProviderStart::Request(const MacSapRequestParamsStart & requestParams)
		{

		}

		void MacSapProviderStart::Response(const MacSapResponseParamsStart & responseParams)
		{

		}
	} // namespace HrWpan

}// namespace ns3
