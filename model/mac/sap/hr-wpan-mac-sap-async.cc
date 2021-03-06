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

#include "hr-wpan-mac-sap-async.h"
#include <ns3/log.h>
#include <ns3/integer.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/hr-wpan-timestamp-tag.h>
#include <ns3/hr-wpan-retrasmission-tag.h>
#include <ns3/hr-wpan-sender-tag.h>
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/simulator.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanMacSapAsync");

	namespace HrWpan
	{

		void MacSapUserAsync::Confirm(const MacSapConfirmParams & confirmParams)
		{
			NS_LOG_FUNCTION(this);
		}

		void MacSapUserAsync::Indication(const MacSapIndicationParams & indicationParams)
		{
			NS_LOG_FUNCTION(this);
			
			const MacSapIndicationParamsAsync & paramsAsync = dynamic_cast< const MacSapIndicationParamsAsync &>(indicationParams);
			
			//Check if the packet is for me
			//Otherwise don't forward

			//NS_LOG_INFO("Address received " << paramsAsync.m_trgtId);

			if (paramsAsync.m_trgtId == m_netDevice->GetMac()->GetDevId() || paramsAsync.m_trgtId == DevId::GetBroadcast())
			{
				//Set the trace to sent
				//NS_LOG_INFO("Packet being forwarded")				

				//HrWpan::SenderTag senderTag;
				//Ptr<Packet> packet = paramsAsync.m_data;

				//packet->PeekPacketTag(senderTag);

				//senderTag.GetSenderMac()->AckReceived(senderTag.GetSenderPacket());

				m_mac->m_macRxTrace(paramsAsync.m_data);
				m_netDevice->Receive(paramsAsync.m_data, paramsAsync.m_orgId);

			}

			

		}

		MacSapUserAsync::MacSapUserAsync(HrWpanNetDevice * netDevice,HrWpanMac * mac) :
			MacSapUser(netDevice,mac)
		{
			NS_LOG_FUNCTION(this);
		}
		
		MacSapProviderAsync::MacSapProviderAsync(HrWpanMac * mac) :
			MacSapProvider(mac)
		{
			NS_LOG_FUNCTION(this);

		}
		
		void MacSapProviderAsync::Request(const MacSapRequestParams & requestParams)
		{
			NS_LOG_FUNCTION(this);

			const MacSapRequestParamsAsync & paramsAsync = dynamic_cast<const MacSapRequestParamsAsync &>(requestParams);
			
			//HrWpanPhyProvider* provider = m_mac->GetPhyProvider();
			// Add header and trailer

			MacHeader header;
			header.setSrcAddress(m_mac->GetDevId());
			header.setDstAddress(paramsAsync.m_trgtId);
			header.SetType(HRWPAN_FRAME_DATA);

			NS_LOG_INFO(paramsAsync.m_trgtId);

			Ptr<Packet> packet = paramsAsync.m_data;
			TimestampTag timestamp;
			timestamp.SetTimestamp(Simulator::Now());
			
			HrWpan::RetrasmissionTag retrasmissionTag;
			retrasmissionTag.SetAttribute("Counter", IntegerValue(0));

			HrWpan::SenderTag senderTag;
			senderTag.SetSenderMac(m_mac);
			senderTag.SetSenderPacket(packet);

			packet->AddHeader(header);
			packet->AddPacketTag(timestamp);
			packet->AddPacketTag(retrasmissionTag);
			packet->AddPacketTag(senderTag);

			m_mac->m_macTxTrace(packet);

			//provider->SendMacPdu(paramsAsync.m_data);
			m_mac->m_queue->Enqueue(packet);
			//NS_LOG_INFO(m_mac->m_queue->GetNPackets());
			m_mac->SendPkt(MicroSeconds(0));

		}

		void MacSapProviderAsync::Response(const MacSapResponseParams & responseParams)
		{
			NS_LOG_FUNCTION(this);

		}



	} //namespace HrWpan

} // namespace ns3