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
#ifndef HR_WPAN_MAC_SAP_START
#define HR_WPAN_MAC_SAP_START

#include "hr-wpan-mac-sap.h"

namespace ns3
{
	class HrWpanMac;

	namespace HrWpan
	{
		class HrWpanNetDevice;

		class MacSapConfirmParamsStart : public MacSapConfirmParams
		{

		};

		class MacSapIndicationParamsStart : public MacSapIndicationParams
		{

		};

		class MacSapUserStart : public MacSapUser
		{
		public:

			MacSapUserStart(HrWpanNetDevice * netDevice);

			virtual void Confirm(const MacSapConfirmParams & confirmParams);
			virtual void Indication(const MacSapIndicationParams & indicationParams);

			virtual std::string GetName() const { return "MacSapUserStart"; }
		};

		class MacSapRequestParamsStart : public MacSapRequestParams
		{

		};

		class MacSapResponseParamsStart : public MacSapResponseParams
		{

		};

		class MacSapProviderStart : public MacSapProvider
		{
		public:
			MacSapProviderStart(HrWpanMac * mac);

			virtual void Request(const MacSapRequestParamsStart & requestParams);
			virtual void Response(const MacSapResponseParamsStart & responseParams);

			virtual std::string GetName() const { return "MacSapProviderStart"; }
		};

	} // namespace HrWpan

}// namespace ns3


#endif //HR_WPAN_MAC_SAP_START
