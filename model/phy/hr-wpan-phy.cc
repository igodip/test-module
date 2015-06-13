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

#include "hr-wpan-phy.h"
#include <ns3/log.h>
#include <ns3/log.h>
#include <ns3/abort.h>
#include <ns3/simulator.h>
#include <ns3/spectrum-value.h>
#include <ns3/antenna-model.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-channel.h>
#include <ns3/packet.h>
#include <ns3/packet-burst.h>
#include <ns3/net-device.h>
#include <ns3/random-variable-stream.h>
#include <ns3/hr-wpan-spectrum-signal-parameters.h>
#include <ns3/hr-wpan-mac.h>

#include <ns3/hr-wpan-net-device.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanPhy");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhy);

	HrWpanPhy::HrWpanPhy() :
		m_psdHelper()
	{
		NS_LOG_FUNCTION(this);

		m_txPsd = m_psdHelper.CreateTxPowerSpectralDensity(0, 1);
		m_stateFactory = CreateObject<HrWpanPhyStateFactory>(GetObject<HrWpanPhy>());
		m_currentState = m_stateFactory->GetIdleState();

		//m_rxSensitivity = pow(10.0, -106.58 / 10.0) / 1000.0; // -102 dbm
	}

	HrWpanPhy::~HrWpanPhy(void)
	{
		NS_LOG_FUNCTION(this);
	}

	void HrWpanPhy::DoDispose()
	{
		NS_LOG_FUNCTION(this);

		//Dispose
		m_stateFactory->Dispose();

		//Resetting pointers
		m_stateFactory = 0;
		m_currentState = 0;
		m_currentPacket = 0;
		
	}

	void HrWpanPhy::DoInitialize()
	{
		//
	}

	TypeId HrWpanPhy::GetTypeId(void)
	{

		static TypeId tid = TypeId("ns3::HrWpanPhy")
			.SetParent<SpectrumPhy>()
			.AddConstructor<HrWpanPhy>().
			AddTraceSource("PhyRxBegin",
			"Trace source indicating a packet has begun"
			"being received from the channel medium by the device",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyRxBeginTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyRxEnd",
			"Trace source indicating a packet has been "
			"completely received from the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyRxEndTrace),
			"ns3::HrWpanPhy::RxEndTracedCallback").
			AddTraceSource("PhyTxBegin",
			"Trace source indicating a packet has begun "
			"being sent to the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyTxBeginTrace),
			"ns3::HrWpanPhy::TxBeginTracedCallback").
			AddTraceSource("PhyTxEnd",
			"Trace source indicating a packet has been"
			"completely sent to the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyTxEndTrace),
			"ns3::HrWpanPhy::TxEndTrace").
			AddTraceSource("PhyTxDrop",
			"Trace source indicating a packet has been"
			"dropped by the device during transmission",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyTxDropTrace),
			"ns3::HrWpanPhy::TxDropTrace").
			AddTraceSource("PhyRxDrop",
			"Trace source indicating a packet has been"
			"dropped by the device during reception",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyRxDropTrace),
			"ns3::HrWpanPhy::RxDropTrace");;

		return tid;
	}

	Ptr<NetDevice> HrWpanPhy::GetDevice(void)
	{

		NS_LOG_FUNCTION(this);

		return m_netdevice;
	}

	void HrWpanPhy::SetDevice(Ptr<NetDevice> netDevice)
	{

		NS_LOG_FUNCTION(this << netDevice);

		m_netdevice = netDevice;
	}

	void HrWpanPhy::SetChannel(Ptr<SpectrumChannel> c)
	{
		NS_LOG_FUNCTION(this << c);
		m_channel = c;
	}

	Ptr<SpectrumChannel> HrWpanPhy::GetChannel(void)
	{
		NS_LOG_FUNCTION(this);
		return m_channel;
	}

	Ptr<const SpectrumModel> HrWpanPhy::GetRxSpectrumModel(void) const
	{
		NS_LOG_FUNCTION(this);
		return NULL;
	}

	Ptr<AntennaModel> HrWpanPhy::GetRxAntenna(void)
	{
		NS_LOG_FUNCTION(this);

		return m_antenna;
	}

	void HrWpanPhy::SetAntenna(Ptr<AntennaModel> a)
	{
		NS_LOG_FUNCTION(this);

		m_antenna = a;
	}

	void HrWpanPhy::SetNoisePowerSpectralDensity(Ptr<const SpectrumValue> noisePsd)
	{
		NS_LOG_FUNCTION(this << noisePsd);
		
		NS_ASSERT(noisePsd);
		m_noise = noisePsd;
	}

	void HrWpanPhy::StartRx(Ptr < SpectrumSignalParameters> spectrumRxParams)
	{

		NS_LOG_FUNCTION(this << spectrumRxParams);

		m_currentState->StartRx(spectrumRxParams);
		
		
	}

	void HrWpanPhy::EndRx(Ptr <SpectrumSignalParameters> spectrumRxParams)
	{
		NS_LOG_FUNCTION(this << spectrumRxParams);

		m_currentState->EndRx(spectrumRxParams);
		
	}

	void HrWpanPhy::StartTx(Ptr<HrWpanSpectrumSignalParameters> spectrumTxParams)
	{
		NS_LOG_FUNCTION(this << spectrumTxParams);

		m_currentState->StartTx(spectrumTxParams);
	}

	void HrWpanPhy::EndTx(Ptr<HrWpanSpectrumSignalParameters> spectrumTxParams)
	{
		NS_LOG_FUNCTION(this << spectrumTxParams);

		m_currentState->EndTx(spectrumTxParams);

	}

	Ptr<MobilityModel> HrWpanPhy::GetMobility(void)
	{
		NS_LOG_FUNCTION(this);
		return (DynamicCast<HrWpan::HrWpanNetDevice>(m_netdevice))->GetNode()->GetObject<MobilityModel>();
	}

	void HrWpanPhy::SetMobility(Ptr<MobilityModel> m)
	{
		
	}

	bool HrWpanPhy::IsRxOn() const {

		NS_LOG_FUNCTION(this);
		return true;
	}

	bool HrWpanPhy::IsTxOn() const {

		NS_LOG_FUNCTION(this);
		return true;

	}

	Time HrWpanPhy::CalculateTxTime(Ptr<const Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		//TODO: It depends on the header of the packet

		Time txTime  = Seconds(packet->GetSize() * 8.0 / 1.0e09);

		return txTime;

	}

	void HrWpanPhy::SendMacPdu(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<HrWpanSpectrumSignalParameters> txParams = Create<HrWpanSpectrumSignalParameters>();
		txParams->duration = CalculateTxTime(p);
		txParams->txPhy = GetObject<SpectrumPhy>();
		txParams->psd = m_txPsd;
		txParams->txAntenna = m_antenna;
		Ptr<PacketBurst> pb = CreateObject<PacketBurst>();
		pb->AddPacket(p);
		txParams->packetBurst = pb;

		StartTx(txParams);
	}

	void HrWpanPhy::SendHrWpanControlMessage(Ptr<HrWpanPhyControlMessage> msg)
	{
		NS_LOG_FUNCTION(this << msg);
		//TODO
	}

	HrWpanPhy* HrWpanPhy::GetPointer() const
	{
		NS_LOG_FUNCTION(this);
		return (HrWpanPhy*) this;
	}

	void HrWpanPhy::SetPhyUser(HrWpanPhyUser * user)
	{
		NS_LOG_FUNCTION(this << user);
		m_phyUser = user;
	}

	HrWpanPhyUser *  HrWpanPhy::GetPhyUser(void) const
	{
		NS_LOG_FUNCTION(this);
		return m_phyUser;
	}

	void HrWpanPhy::RxOn(void)
	{
		m_currentState = m_stateFactory->GetRxOnState();
	}

	void HrWpanPhy::TxOn(void)
	{
		m_currentState = m_stateFactory->GetTxOnState();
	}

} // namespace ns3
