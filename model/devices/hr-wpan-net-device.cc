/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
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
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-net-device.h"
#include <ns3/log.h>
#include <ns3/pointer.h>
#include <ns3/boolean.h>
#include <ns3/abort.h>
#include <ns3/channel.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-channel.h>

namespace ns3
{
	namespace HrWpan
	{
		NS_LOG_COMPONENT_DEFINE("HrWpanNetDevice");

		NS_OBJECT_ENSURE_REGISTERED(HrWpanNetDevice);

		HrWpanNetDevice::HrWpanNetDevice(void) :
			m_configComplete(false)
		{
			NS_LOG_FUNCTION(this);

			m_mac = CreateObject<HrWpanMac>();
			m_phy = CreateObject<HrWpanPhy>();

			CompleteConfig();

		}

		HrWpanNetDevice:: ~HrWpanNetDevice(void)
		{
			NS_LOG_FUNCTION(this);

		}

		TypeId HrWpanNetDevice::GetTypeId(void)
		{
			NS_LOG_FUNCTION_NOARGS();

			static TypeId tid = TypeId("ns3::HrWpan::HrWpanNetDevice")
				.SetParent<NetDevice>()
				.AddConstructor<HrWpanNetDevice>()
				.AddAttribute("Phy", "The PHY layer attached to this device.",
				PointerValue(),
				MakePointerAccessor(&HrWpanNetDevice::GetPhy,
				&HrWpanNetDevice::SetPhy),
				MakePointerChecker<HrWpanPhy>())
				.AddAttribute("Mac", "The MAC layer attached to this device.",
				PointerValue(),
				MakePointerAccessor(&HrWpanNetDevice::GetMac,
				&HrWpanNetDevice::SetMac),
				MakePointerChecker<HrWpanMac>());

			return tid;

		}
		void HrWpanNetDevice::SetIfIndex(const uint32_t index)
		{
			NS_LOG_FUNCTION(this << index);
			m_ifIndex = index;
		}

		uint32_t HrWpanNetDevice::GetIfIndex(void) const
		{
			NS_LOG_FUNCTION(this);
			return m_ifIndex;
		}

		Ptr<Channel> HrWpanNetDevice::GetChannel(void) const
		{
			NS_LOG_FUNCTION(this);
			return m_phy->GetChannel();
		}

		void HrWpanNetDevice::LinkUp(void)
		{
			NS_LOG_FUNCTION(this);
			m_linkUp = true;
			m_linkChanges();
		}

		void HrWpanNetDevice::LinkDown(void)
		{
			NS_LOG_FUNCTION(this);
			m_linkUp = false;
			m_linkChanges();
		}

		bool HrWpanNetDevice::IsLinkUp(void) const
		{
			return m_linkUp;
		}

		void HrWpanNetDevice::SetAddress(Address address)
		{
			NS_LOG_FUNCTION(this);
			//m_mac->SetShortAddress(Mac16Address::ConvertFrom(address));
		}

		Address	HrWpanNetDevice::GetAddress(void) const
		{
			NS_LOG_FUNCTION(this);

			return m_mac->GetDevId();
		}

		bool HrWpanNetDevice::SetMtu(const uint16_t mtu)
		{
			NS_ABORT_MSG("Unsupported");
			return false;
		}

		uint16_t HrWpanNetDevice::GetMtu(void) const
		{
			NS_LOG_FUNCTION(this);
			// Maximum payload size is: max psdu - frame control - seqno - addressing - security - fcs
			//                        = 127      - 2             - 1     - (2+2+2+2)  - 0        - 2
			//                        = 114
			// assuming no security and addressing with only 16 bit addresses without pan id compression.
			return 114;
		}

		bool HrWpanNetDevice::Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
		{

			// This method basically assumes an 802.3-compliant device, but a raw
			// 802.15.4 device does not have an ethertype, and requires specific
			// McpsDataRequest parameters.
			// For further study:  how to support these methods somehow, such as
			// inventing a fake ethertype and packet tag for McpsDataRequest
			NS_LOG_FUNCTION(this << packet << dest << protocolNumber);

			return false;
		}

		Ptr<Node> HrWpanNetDevice::GetNode(void) const
		{
			NS_LOG_FUNCTION(this);

			return m_node;
		}

		void HrWpanNetDevice::SetNode(Ptr<Node> node)
		{
			NS_LOG_FUNCTION(this << node);

			m_node = node;
			CompleteConfig();

		}

		void HrWpanNetDevice::DoDispose(void)
		{
			NS_LOG_FUNCTION(this);
			m_mac->Dispose();
			m_phy->Dispose();
			m_phy = 0;
			m_mac = 0;
			m_node = 0;

			NetDevice::DoDispose();
		}

		void HrWpanNetDevice::DoInitialize(void)
		{
			NS_LOG_FUNCTION(this);
			m_phy->Initialize();
			m_mac->Initialize();
			NetDevice::DoInitialize();
		}

		bool HrWpanNetDevice::NeedsArp(void) const
		{
			NS_LOG_FUNCTION(this);
			return true;
		}

		void HrWpanNetDevice::SetPhy(Ptr<HrWpanPhy> phy)
		{
			NS_LOG_FUNCTION(this << phy);
			m_phy = phy;
			CompleteConfig();
		}

		Ptr<HrWpanPhy> HrWpanNetDevice::GetPhy(void) const
		{
			NS_LOG_FUNCTION(this);
			return m_phy;
		}

		void HrWpanNetDevice::SetMac(Ptr<HrWpanMac> mac)
		{
			NS_LOG_FUNCTION(this << mac);
			m_mac = mac;
			CompleteConfig();
		}

		Ptr<HrWpanMac> HrWpanNetDevice::GetMac(void) const
		{
			NS_LOG_FUNCTION(this);
			return m_mac;
		}

		Address HrWpanNetDevice::GetBroadcast(void) const
		{
			NS_LOG_FUNCTION(this);

			return HrWpanDevId("ff");
		}

		bool HrWpanNetDevice::IsBroadcast(void) const
		{
			NS_LOG_FUNCTION(this);

			return true;
		}

		bool HrWpanNetDevice::IsMulticast(void) const
		{
			NS_LOG_FUNCTION(this);

			return true;
		}

		Address	HrWpanNetDevice::GetMulticast(Ipv4Address multicastGroup) const
		{
			NS_ABORT_MSG("Unimplemented");
			return Address();
		}

		Address	HrWpanNetDevice::GetMulticast(Ipv6Address multicastGroup) const
		{
			NS_ABORT_MSG("Unimplemented");
			return Address();
		}

		bool HrWpanNetDevice::IsBridge(void) const
		{
			NS_LOG_FUNCTION(this);
			return false;
		}

		bool HrWpanNetDevice::IsPointToPoint(void) const
		{
			NS_LOG_FUNCTION(this);
			return false;
		}

		bool HrWpanNetDevice::SendFrom(Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber)
		{
			NS_ABORT_MSG("Unsupported");
			// TODO: To support SendFrom, the MACs McpsDataRequest has to use the provided source address, instead of to local one.
			return false;
		}

		bool HrWpanNetDevice::SupportsSendFrom(void) const
		{
			NS_LOG_FUNCTION(this);
			return false;
		}

		void HrWpanNetDevice::CompleteConfig(void)
		{
			NS_LOG_FUNCTION(this);

			if (m_mac == 0
				|| m_phy == 0
				|| m_node == 0
				|| m_configComplete)
			{
				return;
			}

			m_mac->SetPhyProvider(m_phy->GetPointer());
			m_phy->SetMobility(m_node->GetObject<MobilityModel>());

			m_configComplete = true;
		}

		void HrWpanNetDevice::SetReceiveCallback(ReceiveCallback cb)
		{
			NS_LOG_FUNCTION(this);
			m_receiveCallback = cb;
		}

		void HrWpanNetDevice::SetPromiscReceiveCallback(PromiscReceiveCallback cb)
		{
			NS_LOG_WARN("Unsupported; use HrWpan MAC APIs instead");
		}

		void HrWpanNetDevice::AddLinkChangeCallback(Callback<void> callback)
		{
			NS_LOG_FUNCTION(this);
			m_linkChanges.ConnectWithoutContext(callback);
		}

		void HrWpanNetDevice::SetChannel(Ptr<SpectrumChannel> channel)
		{
			NS_LOG_FUNCTION(this << channel);
			m_phy->SetChannel(channel);
		}

	}// HrWpan namespace

}// ns3 namespace
