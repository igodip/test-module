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

#ifndef HR_WPAN_MAC_H
#define HR_WPAN_MAC_H

#include <ns3/object.h>
#include <ns3/traced-callback.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/hr-wpan-phy-user.h>
#include <ns3/hr-wpan-phy-provider.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-mac-header.h>
#include <ns3/hr-wpan-mac-trailer.h>
#include <ns3/hr-wpan-mac-queue.h>
#include <ns3/mac48-address.h>
#include <ns3/event-id.h>
#include <ns3/simulator.h>

#include <ns3/hr-wpan-mac-manager-listener.h>

#include <ns3/hr-wpan-mac-sap.h>
#include <ns3/hr-wpan-mac-sap-async.h>

#include <cstring>
#include <map>

namespace ns3 {

	

	class HrWpanMac : public Object, public HrWpanPhyUser , public HrWpan::MacManagerListener
	{

		friend class HrWpan::MacSapProviderAsync;
		friend class HrWpan::MacSapUserAsync;

	public:

		HrWpanMac();
		virtual ~HrWpanMac();
		
		static TypeId GetTypeId();

		void AssociatePhyProvider(HrWpanPhyProvider* hrWpanPhyProvider);

		virtual void ReceivePhyPdu(Ptr<Packet> p) ;
		virtual void ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> msg) ;

		HrWpanMac * GetPointer(void) const;

		void SetPhyProvider(HrWpanPhyProvider * provider);
		HrWpanPhyProvider * GetPhyProvider(void) const;

		void McpsDataRequest(Ptr<Packet> p);

		HrWpan::DevId GetDevId() const;
		void SetDevId(HrWpan::DevId devId);

		void RegisterSapUser(HrWpan::MacSapUser * macSapUser);
		
		virtual void SendPkt(Time endTime);

		void SetAddress(const Mac48Address & mac);
		Mac48Address GetAddress() const;

		void SetNetDevice(Ptr<HrWpan::HrWpanNetDevice> netDevice);
		Ptr<HrWpan::HrWpanNetDevice> GetNetDevice() const;

		void AckExpired(Ptr<Packet> packet);
		void AckReceived(Ptr<Packet> packet);

	protected:

		virtual void DoInitialize(void);
		virtual void DoDispose();
		
		TracedCallback<Ptr<const Packet>, uint8_t, uint8_t > m_sentPktTrace;
		TracedCallback<Ptr<const Packet> > m_macTxOkTrace;
		TracedCallback<Ptr<const Packet> > m_macTxDropTrace;
		TracedCallback<Ptr<const Packet> > m_macTxTrace;
		TracedCallback<Ptr<const Packet> > m_macRxTrace;
		TracedCallback<Ptr<const Packet> > m_macRxOkTrace;
		TracedCallback<Ptr<const Packet> > m_macRxDropTrace;
		TracedCallback<Ptr<const Packet> > m_snifferTrace;

	private:

		HrWpanPhyProvider* m_phyProvider;

		HrWpan::DevId m_devId;
		Mac48Address m_macAddress;
		Ptr<HrWpan::MacQueue> m_queue;

		Ptr<HrWpan::HrWpanNetDevice> m_netDevice;

		std::map <std::string, HrWpan::MacSapUser *> m_sapUsers;
		std::map<uint32_t, EventId> m_timeoutPackets;
		
		double m_trasProb;
	};

}

#endif
