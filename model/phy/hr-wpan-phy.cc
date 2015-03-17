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

		m_rxSensitivity = pow(10.0, -106.58 / 10.0) / 1000.0; // -102 dbm
	}

	HrWpanPhy::~HrWpanPhy(void)
	{
		NS_LOG_FUNCTION(this);
	}

	TypeId HrWpanPhy::GetTypeId(void)
	{

		static TypeId tid = TypeId("ns3::HrWpanPhy")
			.SetParent<Object>()
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
			AddTraceSource("PhyTxDropTrace",
			"Trace source indicating a packet has been"
			"dropped by the device during transmission",
			MakeTraceSourceAccessor(&HrWpanPhy::m_phyTxDropTrace),
			"ns3::HrWpanPhy::TxDropTrace");

		return tid;
	}

	void HrWpanPhy::DoDispose(void)
	{

		NS_LOG_FUNCTION(this);

		SpectrumPhy::DoDispose();

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
		NS_LOG_FUNCTION(c);
		m_channel = c;
		m_channel->AddRx(this);
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

		HrWpanSpectrumSignalParameters psdHelper;

		Ptr<HrWpanSpectrumSignalParameters> hrWpanRxParams = DynamicCast<HrWpanSpectrumSignalParameters>(spectrumRxParams);

		// It isn't an our packet
		if (hrWpanRxParams == 0)
		{
			Simulator::Schedule(spectrumRxParams->duration, &HrWpanPhy::EndRx, this, spectrumRxParams);
			return;
		}

		Ptr<Packet> p = (hrWpanRxParams->packetBurst->GetPackets()).front();

		NS_ASSERT(p != 0);

		m_currentState->StartRx(spectrumRxParams);

		Simulator::Schedule(spectrumRxParams->duration, &HrWpanPhy::EndRx, this, spectrumRxParams);
	}

	void HrWpanPhy::EndRx(Ptr <SpectrumSignalParameters> spectrumRxParams)
	{
		NS_LOG_FUNCTION(this << spectrumRxParams);

		Ptr<HrWpanSpectrumSignalParameters> params = DynamicCast<HrWpanSpectrumSignalParameters>(spectrumRxParams);

		if (params != 0)
		{
			Ptr<Packet> packet = params->packetBurst->GetPackets().front();
			((HrWpanMac *) GetPhyUser())->ReceivePhyPdu(packet);
		}

		
	}

	void HrWpanPhy::SetMobility(Ptr<MobilityModel> mobilityModel)
	{
		NS_LOG_FUNCTION(this << mobilityModel);
		m_mobilityModel = mobilityModel;
	}

	Ptr<MobilityModel> HrWpanPhy::GetMobility(void)
	{
		NS_LOG_FUNCTION(this);
		return m_mobilityModel;
	}

	bool HrWpanPhy::IsRxOn() const {

		NS_LOG_FUNCTION(this);
		return true;
	}

	bool HrWpanPhy::IsTxOn() const {

		NS_LOG_FUNCTION(this);
		return true;

	}

	void HrWpanPhy::SendMacPdu(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<HrWpanSpectrumSignalParameters> txParams = Create<HrWpanSpectrumSignalParameters>();
		txParams->duration = MicroSeconds(10);
		txParams->txPhy = GetObject<SpectrumPhy>();
		txParams->psd = m_txPsd;
		txParams->txAntenna = m_antenna;
		Ptr<PacketBurst> pb = CreateObject<PacketBurst>();
		pb->AddPacket(p);
		txParams->packetBurst = pb;
		m_channel->StartTx(txParams);
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

} // namespace ns3
