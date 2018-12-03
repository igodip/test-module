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
#ifndef HR_WPAN_MAC_SAP_ISOCH
#define HR_WPAN_MAC_SAP_ISOCH

#include "hr-wpan-mac-sap.h"
#include "hr-wpan-mac-sap-values.h"

#include <ns3/hr-wpan-dev-id.h>
#include <ns3/packet.h>

namespace ns3
{
	class HrWpanMac;

	namespace HrWpan
	{

		class HrWpanNetDevice;

		class MacSapRequestParamsIsoch : public MacSapRequestParams
		{

		};

		class MacSapResponseParamsIsoch : public MacSapResponseParams
		{

		};

		class MacSapProviderIsoch : MacSapProvider
		{
		public:

			MacSapProviderIsoch(HrWpanMac * mac);

			virtual void Request(const MacSapRequestParamsIsoch & requestParams);
			virtual void Response(const MacSapResponseParamsIsoch & responseParams);

			virtual std::string GetName() const { return "MacSapProviderIsoch"; }
		};

		class MacSapConfirmParamsIsoch : public MacSapConfirmParams
		{

		};

		class MacSapIndicationParamsIsoch : public MacSapIndicationParams
		{

		};

		class MacSapUserIsoch : MacSapUser
		{
		public:

			MacSapUserIsoch(HrWpanNetDevice * netDevice,HrWpanMac * mac);

			virtual void Confirm(const MacSapConfirmParamsIsoch & confirmParams);
			virtual void Indication(const MacSapIndicationParamsIsoch & indicationParams);

			virtual std::string GetName() const { return "MacSapUserIsoch"; }
		};

	} // namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_MAC_SAP_ISOCH