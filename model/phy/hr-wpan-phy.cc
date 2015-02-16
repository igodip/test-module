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
#include <ns3/hr-wpan-spectrum-value-helper.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanPhy");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhy);
	
	HrWpanPhy::HrWpanPhy()
	{
		NS_LOG_FUNCTION(this);

		HrWpanSpectrumValueHelper psdHelper;
		m_txPsd = psdHelper.CreateTxPowerSpectralDensity(0, 1);
	}

	HrWpanPhy::~HrWpanPhy(void)
	{
		NS_LOG_FUNCTION(this);
	}

	TypeId HrWpanPhy::GetTypeId(void) 
	{

		static TypeId tid = TypeId("ns3::HrWpanPhy")
			.SetParent<Object>()
			.AddConstructor<HrWpanPhy>()
			;

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
		//NS_LOG_INFO("\t computed noise_psd: " << *noisePsd);
		NS_ASSERT(noisePsd);
		m_noise = noisePsd;
	}

	void HrWpanPhy::StartRx(Ptr < SpectrumSignalParameters> spectrumRxParams)
	{

		NS_LOG_FUNCTION(this << spectrumRxParams);
		HrWpanSpectrumSignalParameters psdHelper;

		Ptr<HrWpanSpectrumSignalParameters> lrWpanRxParams = DynamicCast<HrWpanSpectrumSignalParameters>(spectrumRxParams);

		if (lrWpanRxParams == 0)
		{

		}

		//NS_LOG_DEBUG(this << " receiving packet with power: " << 10 * log10(HrWpanSpectrumValueHelper::TotalAvgPower(lrWpanRxParams->psd, m_phyPIBAttributes.phyCurrentChannel)) + 30 << "dBm");
		
		

	}

	void HrWpanPhy::EndRx(Ptr <SpectrumSignalParameters> spectrumRxParams)
	{
		NS_LOG_FUNCTION(this << spectrumRxParams);

		if (m_dataIndicationCallback.IsNull())
		{
			m_dataIndicationCallback(10, NULL);
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

	void HrWpanPhy::SetPdDataConfirmationCallback(PdDataConfirmationCallback pd)
	{
		m_dataConfirmationCallback = pd;
	}

	void HrWpanPhy::SetPdDataIndicationCallback(PdDataIndicationCallback pd)
	{
		m_dataIndicationCallback = pd;
	}

	void HrWpanPhy::PdDataRequest(const uint32_t psduLength, Ptr<Packet> packet)
	{
		Ptr<HrWpanSpectrumSignalParameters> txParams = Create<HrWpanSpectrumSignalParameters>();
		txParams->duration = MicroSeconds(10);
		txParams->txPhy = GetObject<SpectrumPhy>();
		txParams->psd = m_txPsd;
		txParams->txAntenna = m_antenna;
		Ptr<PacketBurst> pb = CreateObject<PacketBurst>();
		pb->AddPacket(packet);
		txParams->packetBurst = pb;
		m_channel->StartTx(txParams);
	}
}