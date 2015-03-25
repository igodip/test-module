/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2015
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
* Author:
*	Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-mac.h"
#include <ns3/log.h>
#include <ns3/pointer.h>

#include <ns3/hr-wpan-mac-sap-async.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanMac");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanMac);

	HrWpanMac::HrWpanMac()
	{
		NS_LOG_FUNCTION(this);

	}

	HrWpanMac::~HrWpanMac()
	{
		NS_LOG_FUNCTION(this);
	}

	TypeId HrWpanMac::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::HrWpanMac")
			.SetParent<Object>()
			.AddConstructor<HrWpanMac>()
			.AddTraceSource("MacTx",
			"Trace source indicating a packet has"
			"arrived for transmission by this device",
			MakeTraceSourceAccessor(&HrWpanMac::m_macTxTrace),
			"ns3::Packet::TracedCallback")
			.AddTraceSource("MacTxOk",
			"Trace source indicating a packet has"
			"been successfully sent",
			MakeTraceSourceAccessor(&HrWpanMac::m_macTxOkTrace),
			"ns3::Packet::TracedCallback")
			.AddTraceSource("MacTxDrop",
			"Trace source indicating a packet has"
			"been dropped during transmission",
			MakeTraceSourceAccessor(&HrWpanMac::m_macTxDropTrace),
			"ns3::Packet::TracedCallback")
			.AddTraceSource("MacRx",
			"A packet has been received by this device, "
			"has been passed up from the physical layer "
			"and is being forwarded up the local protocol stack.  "
			"This is a non-promiscuous trace,",
			MakeTraceSourceAccessor(&HrWpanMac::m_macRxTrace),
			"ns3::Packet::TracedCallback")
			.AddTraceSource("MacRxDrop",
			"Trace source indicating a packet was received, "
			"but dropped before being forwarded up the stack",
			MakeTraceSourceAccessor(&HrWpanMac::m_macRxDropTrace),
			"ns3::Packet::TracedCallback")
			.AddTraceSource("Sniffer",
			"Trace source simulating a non-promiscuous "
			"packet sniffer attached to the device",
			MakeTraceSourceAccessor(&HrWpanMac::m_snifferTrace),
			"ns3::Packet::TracedCallback")
			.AddAttribute("Queue", "The Mac queue",
			PointerValue(),
			MakePointerAccessor(&HrWpanMac::m_queue),
			MakePointerChecker<HrWpan::MacQueue>());

		return tid;
	}

	void HrWpanMac::AckWaitTimeout(void)
	{
		NS_LOG_FUNCTION(this);

	}

	void HrWpanMac::PrepareRetransmission(void)
	{
		NS_LOG_FUNCTION(this);

	}

	void HrWpanMac::DoDispose()
	{
		NS_LOG_FUNCTION(this);

		Object::DoDispose();
	}

	void HrWpanMac::AssociatePhyProvider(HrWpanPhyProvider* hrWpanPhyProvider)
	{
		NS_LOG_FUNCTION(this << hrWpanPhyProvider);

		m_phyProvider = hrWpanPhyProvider;

	}

	void HrWpanMac::ReceivePhyPdu(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);
		
		HrWpan::MacHeader header;

		p->RemoveHeader(header);

		HrWpan::MacSapIndicationParamsAsync indicationParams;
		indicationParams.m_data = p;
		indicationParams.m_orgId = header.getSrcAddress();
		indicationParams.m_trgtId = header.getDstAddress();

		//Switch but for now only forward
		m_sapUsers["MacSapUserAsync"]->Indication(indicationParams);

	}

	void HrWpanMac::ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> cMsg)
	{
		NS_LOG_FUNCTION(this << cMsg);

	}

	void HrWpanMac::DoInitialize(void)
	{
		NS_LOG_FUNCTION(this);


		Object::DoInitialize();
		m_queue = CreateObject<HrWpan::MacQueue>();
		
	}

	HrWpanMac * HrWpanMac::GetPointer(void) const
	{
		NS_LOG_FUNCTION(this);

		return (HrWpanMac *)this;
	}

	void HrWpanMac::SetPhyProvider(HrWpanPhyProvider * provider)
	{
		NS_LOG_FUNCTION(this << provider);

		m_phyProvider = provider;

	}

	HrWpanPhyProvider * HrWpanMac::GetPhyProvider(void) const
	{
		NS_LOG_FUNCTION(this);

		return m_phyProvider;
	}

	void HrWpanMac::McpsDataRequest(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);
		
		//m_phyProvider->SendMacPdu(packet);
		m_queue->Enqueue(packet);
	}

	void HrWpanMac::SetDevId(HrWpanDevId devId)
	{
		m_devId = devId;
	}

	HrWpanDevId HrWpanMac::GetDevId(void) const
	{
		NS_LOG_FUNCTION(this);
		return m_devId;
	}

	void HrWpanMac::RegisterSapUser(HrWpan::MacSapUser * macSapUser)
	{
		NS_LOG_FUNCTION(this << macSapUser);
		m_sapUsers[macSapUser->GetName()] = macSapUser;

	}

	void HrWpanMac::SendPkt()
	{
		NS_LOG_FUNCTION(this);

		Ptr<Packet> packet = m_queue->Dequeue();

		if (packet == 0)
		{
			NS_LOG_INFO("No packet inside queue!");
			return;
		}

		m_phyProvider->SendMacPdu(packet);
	}

	void HrWpanMac::SetAddress(const Mac48Address & mac)
	{
		NS_LOG_FUNCTION(this);

		m_macAddress = mac;

	}

	Mac48Address HrWpanMac::GetAddress() const
	{
		NS_LOG_FUNCTION(this);

		return m_macAddress;

	}

} //namespace ns3