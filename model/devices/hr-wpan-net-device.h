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

#ifndef HR_WPAN_NET_DEVICE_H
#define HR_WPAN_NET_DEVICE_H

#include <ns3/net-device.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-phy.h>
#include <ns3/node.h>

namespace ns3 {


	namespace HrWpan
	{
		
		class HrWpanNetDevice : public NetDevice {

		public:

			static TypeId GetTypeId(void);

			HrWpanNetDevice(void);
			virtual ~HrWpanNetDevice(void);

			void SetMac(Ptr<HrWpanMac> mac);
			Ptr<HrWpanMac> GetMac(void) const;

			void SetPhy(Ptr<HrWpanPhy> phy);
			Ptr<HrWpanPhy> GetPhy(void) const;

			void SetChannel(Ptr<SpectrumChannel> channel);

			//From NetDevice
			virtual void SetIfIndex(const uint32_t index);
			virtual uint32_t GetIfIndex(void) const;
			virtual Ptr<Channel> GetChannel(void) const;
			virtual void SetAddress(Address address);
			virtual Address GetAddress(void) const;
			virtual bool SetMtu(const uint16_t mtu);
			virtual uint16_t GetMtu(void) const;
			virtual bool IsLinkUp(void) const;
			virtual void AddLinkChangeCallback(Callback<void> callback);
			virtual bool IsBroadcast(void) const;
			virtual Address GetBroadcast(void) const;
			virtual bool IsMulticast(void) const;
			virtual Address GetMulticast(Ipv4Address multicastGroup) const;
			virtual Address GetMulticast(Ipv6Address addr) const;
			virtual bool IsBridge(void) const;
			virtual bool IsPointToPoint(void) const;
			virtual bool Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);
			virtual bool SendFrom(Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
			virtual Ptr<Node> GetNode(void) const;
			virtual void SetNode(Ptr<Node> node);
			virtual bool NeedsArp(void) const;

			virtual void SetReceiveCallback(NetDevice::ReceiveCallback cb);
			virtual void SetPromiscReceiveCallback(PromiscReceiveCallback cb);
			virtual bool SupportsSendFrom(void) const;

		protected:

			virtual void DoDispose(void);
			virtual void DoInitialize(void);

			void LinkUp(void);
			void LinkDown(void);

			void CompleteConfig(void);
			/**
			* The MAC for this NetDevice.
			*/
			Ptr<HrWpanMac> m_mac;

			/**
			* The PHY for this NetDevice.
			*/
			Ptr<HrWpanPhy> m_phy;

			/**
			* The node associated with this NetDevice.
			*/
			Ptr<Node> m_node;

			TracedCallback<> m_linkChanges;

			ReceiveCallback m_receiveCallback;

			/**
			* Is the link/device currently up and running?
			*/
			bool m_linkUp;

			/** \brief	Interface index of this NetDevice */
			uint32_t m_ifIndex;

			bool m_configComplete;
		};

	} //namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_NET_DEVICE