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

#ifndef HR_WPAN_MAC_SAP_ASYNC_H
#define HR_WPAN_MAC_SAP_ASYNC_H

#include "hr-wpan-mac-sap.h"
#include "hr-wpan-mac-sap-values.h"

#include <ns3/hr-wpan-dev-id.h>
#include <ns3/packet.h>

namespace ns3
{
	namespace HrWpan
	{

		using namespace Mac;

		class MacSapIndicationParamsAsync : public MacSapIndicationParams
		{
		public:
			HrWpanDevId m_trgtId;
			HrWpanDevId m_orgId;
			SNAPHeaderPresent m_snapHeaderPresent;
			Length length;
			Ptr<Packet> m_data;

			virtual ~MacSapIndicationParamsAsync() {}
		};

		class MacSapConfirmParamsAsync : public MacSapConfirmParams
		{
		public:
			RequestId m_requestId;
			TransmitDelay m_transmitDelay;
			ResultCode m_resultCode;
			ReasonCode m_reasonCode;

			virtual ~MacSapConfirmParamsAsync() {}
		};

		class MacSapUserAsync : public MacSapUser
		{
		public:
			MacSapUserAsync(HrWpanNetDevice * netDevice,HrWpanMac * mac);

			virtual void Confirm(const MacSapConfirmParams & confirmParams);
			virtual void Indication(const MacSapIndicationParams & indicationParams);

			virtual std::string GetName() const { return "MacSapUserAsync"; }

		};

		class MacSapRequestParamsAsync : public MacSapRequestParams
		{
		public:
			RequestId m_requestId;
			HrWpanDevId m_trgtId;
			TransmitTimeout m_transmitTimeout;
			MaxRetries m_maxRetries;
			SNAPHeaderPresent m_snapHeaderPresent;
			UserPriority m_userPriority;
			ACKRequested m_ackRequested;
			ConfirmRequested m_confirmRequested;
			Length m_length;
			Ptr<Packet> m_data;
			
			virtual ~MacSapRequestParamsAsync() {}

		};

		class MacSapResponseParamsAsync : public MacSapResponseParams
		{
			virtual ~MacSapResponseParamsAsync() {}
		};

		class MacSapProviderAsync : public MacSapProvider
		{
		public:
			MacSapProviderAsync(HrWpanMac * mac);

			virtual void Request(const MacSapRequestParams & requestParams);
			virtual void Response(const MacSapResponseParams & responseParams);

			virtual std::string GetName() const { return "MacSapProviderAsync"; }

		};

	} // namespace HrWpan


} // namespace ns3

#endif //HR_WPAN_MAC_SAP_ASYNC_H