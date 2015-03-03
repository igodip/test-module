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
#ifndef HR_WPAN_MAC_SAP_H
#define HR_WPAN_MAC_SAP_H

#include <ns3/object.h>

#include <cstring>


namespace ns3
{
	class HrWpanMac;
	

	namespace HrWpan
	{

		class HrWpanNetDevice;

		class MacSapUser
		{
		public:

			class MacSapConfirmParams
			{

			};

			class MacSapIndicationParams
			{

			};

			MacSapUser(HrWpanNetDevice * netDevice);

			virtual void Confirm (const MacSapConfirmParams & confirmParams) {}
			virtual void Indication (const MacSapIndicationParams & indicationParams) {}

			virtual std::string GetName() const { return ""; }

		protected:
			HrWpanNetDevice * m_netDevice;

		};

		class MacSapProvider
		{

		public:

			MacSapProvider(HrWpanMac * mac);

			class MacSapRequestParams
			{

			};

			class MacSapResponseParams
			{

			};

			virtual void Request (const MacSapRequestParams & requestParams) {};
			virtual void Response (const MacSapResponseParams & responseParams) {};

			virtual std::string GetName() const { return ""; }

		protected:
			HrWpanMac * m_mac;
		};

	}// namespace HrWpan

} // namespace ns3

#endif //HR_WPAN_MAC_SAP_H