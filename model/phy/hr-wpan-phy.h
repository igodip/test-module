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

#ifndef HR_WPAN_PHY_H
#define HR_WPAN_PHY_H

#include <ns3/spectrum-phy.h>
#include <ns3/traced-callback.h>
#include <ns3/event-id.h>

namespace ns3 {

	class Packet;

	/**
	 * \typedef	Callback<void, uint32_t, Ptr<Packet>, uint8_t> PdDataIndicationCallback
	 *
	 * \brief	Defines an alias representing the pd data indication callback.
	 */

	typedef Callback<void, uint32_t, Ptr<Packet>, uint8_t> PdDataIndicationCallback;


	class HrWpanPhy : public SpectrumPhy {
	public:
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

		virtual void DoDispose();

	private:

		/** \brief	The mobility model. */
		Ptr<MobilityModel> m_mobilityModel;

		/** \brief	The antenna. */
		Ptr<AntennaModel> m_antenna;

		Ptr<NetDevice> m_netdevice;

		TracedCallback<Ptr<const Packet> > m_phyRxBeginTrace;

		TracedCallback<Ptr<const Packet>, double > m_phyRxEndTrace;

		Ptr<const SpectrumValue> m_noise;
	};

}

#endif