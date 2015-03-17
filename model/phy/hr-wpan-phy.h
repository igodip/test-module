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
* Author:
*	Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#ifndef HR_WPAN_PHY_H
#define HR_WPAN_PHY_H

#include <ns3/spectrum-phy.h>
#include <ns3/traced-callback.h>
#include <ns3/event-id.h>
#include <ns3/hr-wpan-spectrum-value-helper.h>

#include "hr-wpan-phy-attributes.h"

#include <ns3/hr-wpan-phy-state-factory.h>
#include <ns3/hr-wpan-phy-provider.h>
#include <ns3/hr-wpan-phy-user.h>
#include <ns3/hr-wpan-interference-helper.h>

namespace ns3 {

	class Packet;
	class SpectrumValue;
	class HrWpanErrorModel;
	//struct HrWpanSpectrumSignalParameters;
	class MobilityModel;
	class SpectrumChannel;
	class SpectrumModel;
	class AntennaModel;
	class NetDevice;
	class UniformRandomVariable;

	class HrWpanPhy : public SpectrumPhy, public HrWpanPhyProvider {
	public:

		//Friends
		friend class HrWpanRxOnState;
		friend class HrWpanRxBusyState;

		static TypeId GetTypeId(void);

		HrWpanPhy(void);
		virtual ~HrWpanPhy(void);

		void SetMobility(Ptr<MobilityModel> m);
		Ptr<MobilityModel> GetMobility(void);

		void SetChannel(Ptr<SpectrumChannel> c);
		Ptr<SpectrumChannel> GetChannel(void);

		void SetDevice(Ptr<NetDevice> d);
		Ptr<NetDevice> GetDevice(void);

		void SetAntenna(Ptr<AntennaModel> a);
		Ptr<AntennaModel> GetRxAntenna(void);

		virtual Ptr<const SpectrumModel> GetRxSpectrumModel(void) const;
		void SetTxPowerSpectralDensity(Ptr<SpectrumValue> txPsd);

		void SetNoisePowerSpectralDensity(Ptr<const SpectrumValue> noisePsd);
		Ptr<const SpectrumValue> GetNoisePowerSpectralDensity(void);

		void StartRx(Ptr<SpectrumSignalParameters> spectrumRxParams);
		void EndRx(Ptr<SpectrumSignalParameters> params);

		virtual void DoDispose();

		//Rx methods
		bool IsRxOn() const;
		void RxOn();

		//Tx methods
		bool IsTxOn() const;
		void TxOn();

		//HrWpanPhyProvider
		virtual void SendMacPdu(Ptr<Packet> p);
		virtual void SendHrWpanControlMessage(Ptr<HrWpanPhyControlMessage> msg);
		
		void SetPhyUser(HrWpanPhyUser* phyUser);
		HrWpanPhyUser* GetPhyUser() const;

		HrWpanPhy* GetPointer() const;

	private:

		/** \brief	The mobility model. */
		Ptr<MobilityModel> m_mobilityModel;

		/** \brief	The antenna. */
		Ptr<AntennaModel> m_antenna;

		/** \brief	The net device. */
		Ptr<NetDevice> m_netdevice;
		
		/** \brief	The channel. */
		Ptr<SpectrumChannel> m_channel;

		TracedCallback<Ptr<const Packet> > m_phyRxBeginTrace;
		TracedCallback<Ptr<const Packet>, double > m_phyRxEndTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxDropTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxEndTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxBeginTrace;

		/** \brief	The noise. */
		Ptr<const SpectrumValue> m_noise;

		double m_rxSensitivity;
		
		Ptr<SpectrumValue> m_txPsd;

		HrWpanSpectrumValueHelper m_psdHelper;

		Ptr<HrWpanPhyAbsState> m_currentState;
		Ptr<HrWpanPhyStateFactory> m_stateFactory;

		HrWpanPhyUser* m_phyUser;
	};

}

#endif
