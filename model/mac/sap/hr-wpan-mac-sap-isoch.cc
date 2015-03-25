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
#include "hr-wpan-mac-sap-isoch.h"

#include <ns3/hr-wpan-net-device.h>
#include <ns3/hr-wpan-mac.h>

#include <ns3/log.h>
#include <ns3/abort.h>

namespace ns3
{

	class HrWpanMac;

	namespace HrWpan
	{

		class HrWpanNetDevice;

		MacSapProviderIsoch::MacSapProviderIsoch(HrWpanMac * mac) :
			MacSapProvider(mac)
		{

		}

		void MacSapProviderIsoch::Request(const MacSapRequestParamsIsoch & requestParams)
		{

		}

		void MacSapProviderIsoch::Response(const MacSapResponseParamsIsoch & responseParams)
		{

		}


		MacSapUserIsoch::MacSapUserIsoch(HrWpanNetDevice * netDevice,HrWpanMac * mac) :
			MacSapUser(netDevice,mac)
		{

		}

		void MacSapUserIsoch::Confirm(const MacSapConfirmParamsIsoch & confirmParams)
		{

		}

		void MacSapUserIsoch::Indication(const MacSapIndicationParamsIsoch & indicationParams)
		{

		}



	} // namespace hrWpan

}// namespace ns3