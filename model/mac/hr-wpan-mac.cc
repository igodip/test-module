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
#include <ns3/hash.h>
#include <ns3/pointer.h>
#include <ns3/simulator.h>

#include <ns3/hr-wpan-mac-sap-async.h>
#include <ns3/hr-wpan-net-device.h>

#include <ns3/random-variable-stream.h>
#include <ns3/double.h>
#include <ns3/hr-wpan-retrasmission-tag.h>

#include <algorithm>


namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanMac");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanMac);

	HrWpanMac::HrWpanMac()
	{
		NS_LOG_FUNCTION(this);

		m_queue = CreateObject<HrWpan::MacQueue>();

		m_rtsSent = false;
		m_ctsSent = false;
		m_dataSent = false;

		m_tryNumber = 0;

		m_ctrlFactory = & HrWpanCtrlPacketFactory::getInstance();
		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(1.0));
		m_urv->SetAttribute("Max", DoubleValue(1024.0));

		m_turnToWait = 0;

	}

	HrWpanMac::~HrWpanMac()
	{
		NS_LOG_FUNCTION(this);

		std::map< std::string, HrWpan::MacSapUser * >::iterator i = m_sapUsers.begin();

		while (i == m_sapUsers.end())
		{
			delete ((HrWpan::MacSapUserAsync * ) i->second);
			i++;
		}

		m_sapUsers.clear();
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
			MakePointerChecker<HrWpan::MacQueue>())
			.AddAttribute("TrasProb","The Trasmission probability",
			DoubleValue(1),
			MakeDoubleAccessor(&HrWpanMac::m_trasProb),
			MakeDoubleChecker<double>());

		return tid;
	}


	void HrWpanMac::DoDispose()
	{
		NS_LOG_FUNCTION(this);
		m_queue->Dispose();
		m_timeoutPackets.clear();
		
		m_netDevice = 0;
		m_queue = 0;
	}

	void HrWpanMac::AssociatePhyProvider(HrWpanPhyProvider* hrWpanPhyProvider)
	{
		NS_LOG_FUNCTION(this << hrWpanPhyProvider);

		m_phyProvider = hrWpanPhyProvider;

	}

	void HrWpanMac::ReceivePhyPdu(Ptr<Packet> p)
	{

		//Check if cts / rts

		NS_LOG_FUNCTION(this << p);
		NS_LOG_INFO(GetDevId() << " Receiving a packet");

		HrWpan::MacHeader header;

		p->PeekHeader(header);

		/*if (header.getDstAddress() != GetDevId())
		{
			NS_LOG_INFO(GetDevId() << " Packet discarded not for me");

			return;
		}*/

		if (header.IsCommand())
		{
			//RTS or CTS Packet
			NS_LOG_INFO(GetDevId() << " Command");


			if (m_rtsSent == true)
			{
				NS_LOG_INFO(GetDevId() << " Cts Received");
				m_evtWaitingCts.Cancel();
				SendData(p);
				//So it's cts
			}
			/*else
			{
				//So it's rts
				NS_LOG_INFO(GetDevId() << " Rts Received");
				SendCts(p);
			}*/
                        else if (GetDevId() == "00:02") //if(header.IsCommand()) {xcorr(header.getRtsCssSeq, refRtsSeq) if (match){Rts rvd}}
                        {
                                NS_LOG_INFO(GetDevId() << "Rts Received");
                                SendCts(p);
                        }

			return;
		}


		if (header.IsImmediateAck())
		{
			//Ack received
			NS_LOG_INFO(GetDevId() << " Imm Ack Received");
			m_evtWaitingAck.Cancel();
			AckReceived(p);
			return;

		}

		NS_LOG_INFO(GetDevId() << " Data received");

		HrWpan::MacSapIndicationParamsAsync indicationParams;
		indicationParams.m_data = p;
		indicationParams.m_orgId = header.getSrcAddress();
		indicationParams.m_trgtId = header.getDstAddress();

		//Switch but for now only forward
		m_sapUsers["MacSapUserAsync"]->Indication(indicationParams);

		// Data received
		m_evtWaitingData.Cancel();
		//Send Ack

		SendAck(p);

	}

	void HrWpanMac::ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> cMsg)
	{
		NS_LOG_FUNCTION(this << cMsg);

	}

	void HrWpanMac::DoInitialize(void)
	{
		NS_LOG_FUNCTION(this);


		Object::DoInitialize();
		
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
		
		//Check which type of packet we have received
		//RTS -> so send a CTS back
		//CTS -> send Data
		//DATA -> 
		//ACK -> ack recevied

		m_queue->Enqueue(packet);
	}

	void HrWpanMac::SetDevId(HrWpan::DevId devId)
	{
		NS_LOG_FUNCTION(this);
		m_devId = devId;
	}

	HrWpan::DevId HrWpanMac::GetDevId(void) const
	{
		NS_LOG_FUNCTION(this);
		return m_devId;
	}

	void HrWpanMac::RegisterSapUser(HrWpan::MacSapUser * macSapUser)
	{
		NS_LOG_FUNCTION(this << macSapUser);
		m_sapUsers[macSapUser->GetName()] = macSapUser;

	}

	void HrWpanMac::SendPkt(Time remTime)
	{
		NS_LOG_FUNCTION(this);

		//If scheduled a retrasmission
		if (m_evtTrasmission.IsRunning())
		{
			NS_LOG_INFO(GetDevId() << " Already scheduled sent");
			return;
		}

		//Check for Carrier sense
		NS_LOG_INFO(GetDevId() << " Checking for carrier sense");

		m_phyProvider->RxOn();

		if (!m_phyProvider->IsChannelIdle())
		{
			NS_LOG_WARN(GetDevId() << " channel is not Idle");
			RescheduleTrasmission(true);

			return;
		}

		if (m_queue->GetNPackets() == 0)
		{
			NS_LOG_INFO(GetDevId() << "No packets in queue");
			return;
		}

		
		m_phyProvider->TxOn();

		SendRts();
		
	}

	void HrWpanMac::SendRts()
	{
		NS_LOG_FUNCTION(this);

		Ptr<const Packet> p = m_queue->Peek();
		NS_LOG_INFO(GetDevId() << " Sending Rts " << m_queue->GetNPackets());

		HrWpan::MacHeader header;
		p->PeekHeader(header);
		/*HrWpan::DevId receiver = header.getDstAddress();
		HrWpan::DevId sender = header.getSrcAddress();*/
                std::vector<std::complex<double> > rtsCssSequences = header.getRtsCssSequence();
		
		//Ptr<Packet> p2 = m_ctrlFactory->CreateRtsPacket(receiver, sender, MicroSeconds(200));
                Ptr<Packet> p2 = m_ctrlFactory->CreateRtsPacket(rtsCssSequences, MicroSeconds(200));
		HrWpan::MacHeader headerRts;
		//headerRts.SetType(HrWpan::HRWPAN_FRAME_COMMAND);
		/*headerRts.setDstAddress(header.getDstAddress());
		headerRts.setSrcAddress(header.getSrcAddress());*/
                headerRts.setRtsCssSequence(header.getRtsCssSequence());
                headerRts.setDuration(header.getDuration());

		p2->AddHeader(headerRts);
		
		m_phyProvider->SendMacPdu(p2);

		m_evtWaitingCts = Simulator::Schedule(MicroSeconds(5.0), &HrWpanMac::CtsExpired, this);

		//Turn Rx On
		m_phyProvider->RxOn();
		m_rtsSent = true;
	}

	

	void HrWpanMac::CtsExpired()
	{
		NS_LOG_FUNCTION(this);
		//Reset all
		RescheduleTrasmission(true);
		
		m_rtsSent = false;
	}

	void HrWpanMac::SendCts(Ptr<const Packet> rts)
	{
		NS_LOG_FUNCTION(this);

		m_phyProvider->TxOn();

		HrWpan::MacHeader header;

		rts->PeekHeader(header);

		//Check that rts is for me
		if (header.getDstAddress() != GetDevId())
		{
			NS_LOG_WARN(GetDevId() << "Rts was not for me");

			m_ctsSent = false;
			m_rtsSent = false;
			m_dataSent = false;

			//RescheduleTrasmission(true);

			return;
		}
		//HrWpan::DevId receiver = header.getDstAddress();
		HrWpan::DevId sender = header.getSrcAddress();

		Ptr<Packet> cts = m_ctrlFactory->CreateCtsPacket(sender, MicroSeconds(200));

		HrWpan::MacHeader headerCts;
		headerCts.SetType(HrWpan::HRWPAN_FRAME_COMMAND);
		//NS_LOG_INFO(header.getSrcAddress());

		headerCts.setDstAddress(header.getSrcAddress());
		headerCts.setSrcAddress(GetDevId());

		NS_LOG_INFO(GetDevId() << " Sending Cts");

		cts->AddHeader(headerCts);
		m_phyProvider->SendMacPdu(cts);

		m_evtWaitingData = Simulator::Schedule(MicroSeconds(5.0), &HrWpanMac::DataExpired, this);

		m_phyProvider->RxOn();
		m_ctsSent = true;

	}

	void HrWpanMac::DataExpired()
	{
		NS_LOG_FUNCTION(this);

		m_ctsSent = false;
		m_rtsSent = false;
		m_dataSent = false;

		RescheduleTrasmission(true);
		m_phyProvider->RxOn();
	}


	void HrWpanMac::AckReceived(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this);

		NS_LOG_INFO(GetDevId() << " Ack received");

		if (m_queue->GetNPackets() != 0)
		{
			RescheduleTrasmission(false);
		}
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

	void HrWpanMac::SetNetDevice(Ptr<HrWpan::HrWpanNetDevice> netDevice)
	{
		NS_LOG_FUNCTION(this);

		m_netDevice = netDevice;

	}

	Ptr<HrWpan::HrWpanNetDevice> HrWpanMac::GetNetDevice() const
	{
		NS_LOG_FUNCTION(this);

		return m_netDevice;

	}

	void HrWpanMac::AckExpired(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		NS_LOG_INFO(GetDevId() << " Ack Expired");

		m_queue->PushFront(packet);
		RescheduleTrasmission(true);

		return;
	}

	void HrWpanMac::SendData(Ptr<const Packet> cts)
	{
		NS_LOG_FUNCTION(this);

		m_rtsSent = false;
		m_ctsSent = false;

		//Check that cts was for me
		HrWpan::MacHeader header;
		cts->PeekHeader(header);

		//NS_LOG_INFO(header.getDstAddress());

		if (header.getDstAddress() != GetDevId())
		{
			NS_LOG_WARN(GetDevId() << "Cts was not for me");

			m_ctsSent = false;
			m_rtsSent = false;
			m_dataSent = false;

			RescheduleTrasmission(true);

			return;
		}
		
		m_phyProvider->TxOn();

		Ptr<Packet> p = m_queue->Dequeue();
		m_phyProvider->SendMacPdu(p);

		NS_LOG_INFO(GetDevId() << " Sending Data");

		m_evtWaitingAck = Simulator::Schedule(MicroSeconds(5.0), &HrWpanMac::AckExpired, this, p);
	}

	void HrWpanMac::SendAck(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this);

		NS_LOG_INFO(GetDevId() << " Sending Ack");


		HrWpan::MacHeader header;
		p->PeekHeader(header);

		m_phyProvider->TxOn();

		Ptr<Packet> p2 = HrWpanCtrlPacketFactory::getInstance().CreateAckPacket(header.getSrcAddress(), 0);

		HrWpan::MacHeader headerAck;
		headerAck.SetType(HrWpan::HRWPAN_FRAME_IMM_ACK);
		headerAck.setDstAddress(header.getSrcAddress());
		headerAck.setSrcAddress(header.getDstAddress());

		p2->AddHeader(headerAck);

		m_phyProvider->SendMacPdu(p2);

		
	}

	void HrWpanMac::RescheduleTrasmission(bool collision)
	{
		NS_LOG_FUNCTION(this);

		if (collision == false)
		{
			m_tryNumber = 0;
		}

		//NS_LOG_ERROR("Rescheduling trasmission");

		m_tryNumber++;
		m_tryNumber = m_tryNumber > 10 ? 10 : m_tryNumber;
		uint32_t slots = 1 << m_tryNumber;
		Time waitTime = MicroSeconds(5.0) * (m_urv->GetInteger() % slots);
		NS_LOG_ERROR(GetDevId()  << "Time waiting " << waitTime);

		m_evtTrasmission = Simulator::Schedule(waitTime, &HrWpanMac::SendPkt, this, Seconds(0));


	}

	

} //namespace ns3
