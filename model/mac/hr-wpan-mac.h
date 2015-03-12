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
#include <ns3/mac48-address.h>
#include <ns3/event-id.h>

#include <ns3/hr-wpan-mac-sap.h>

#include <cstring>
#include <map>

namespace ns3 {

	class HrWpanMac : public Object, public HrWpanPhyUser{
	public:
		HrWpanMac();
		virtual ~HrWpanMac();
		
		static TypeId GetTypeId();

		void AssociatePhyProvider(HrWpanPhyProvider* hrWpanPhyProvider);

		virtual void ReceivePhyPdu(Ptr<Packet> p) ;
		virtual void ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> msg) ;

		void AckWaitTimeout(void);
		void PrepareRetransmission(void);

		HrWpanMac * GetPointer(void) const;

		void SetPhyProvider(HrWpanPhyProvider * provider);
		HrWpanPhyProvider * GetPhyProvider(void) const;

		void McpsDataRequest(Ptr<Packet> p);

		HrWpanDevId GetDevId() const;
		void SetDevId(HrWpanDevId devId);

		void RegisterSapUser(HrWpan::MacSapUser * macSapUser);
		

	protected:

		virtual void DoInitialize(void);
		virtual void DoDispose();
		

	private:

		HrWpanPhyProvider* m_phyProvider;

		HrWpanDevId m_devId;
		Mac48Address m_macAddress;
		
		TracedCallback<Ptr<const Packet>, uint8_t, uint8_t > m_sentPktTrace;
		TracedCallback<Ptr<const Packet> > m_macTxOkTrace;
		TracedCallback<Ptr<const Packet> > m_macTxDropTrace;
		TracedCallback<Ptr<const Packet> > m_macTxTrace;
		TracedCallback<Ptr<const Packet> > m_macRxTrace;
		TracedCallback<Ptr<const Packet> > m_macRxOkTrace;
		TracedCallback<Ptr<const Packet> > m_macRxDropTrace;

		EventId m_ackWaitTimeout;

		std::map <std::string, HrWpan::MacSapUser *> m_sapUsers;
		

	};

}

#endif
