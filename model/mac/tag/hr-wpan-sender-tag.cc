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

#include "hr-wpan-sender-tag.h"
#include <ns3/pointer.h>
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::SenderTag");

	namespace HrWpan
	{
		TypeId	SenderTag::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpan::SenderTag")
				.SetParent<Tag>()
				.AddConstructor<SenderTag>();

			return tid;
		}

		TypeId	SenderTag::GetInstanceTypeId(void) const
		{
			return GetTypeId();
		}

		uint32_t SenderTag::GetSerializedSize(void) const
		{
			return sizeof(Ptr<HrWpanMac>)+sizeof(Ptr<Packet>);
		}

		void SenderTag::Serialize(TagBuffer i) const
		{
			NS_LOG_FUNCTION(this << m_senderMac << m_senderPacket);

			i.Write((uint8_t*)(&m_senderMac), sizeof(Ptr<HrWpanMac>));
			i.Write((uint8_t*)(&m_senderPacket), sizeof(Ptr<Packet>));

		}

		void SenderTag::Deserialize(TagBuffer i)
		{
			NS_LOG_FUNCTION(this << m_senderMac << m_senderPacket);
			
			i.Read(((uint8_t*) & m_senderMac), sizeof(Ptr<HrWpanMac>));
			i.Read(((uint8_t* ) & m_senderPacket), sizeof(Ptr<Packet>));

			//Magic
			m_senderMac->Ref();
			m_senderPacket->Ref();
			
		}

		void SenderTag::SetSenderMac(Ptr<HrWpanMac> mac)
		{
			NS_LOG_FUNCTION(this << mac);
			m_senderMac = mac;
		}

		void SenderTag::SetSenderPacket(Ptr<Packet> packet)
		{
			NS_LOG_FUNCTION(this << packet);
			m_senderPacket = packet;
		}

		Ptr<HrWpanMac> SenderTag::GetSenderMac() const
		{
			return m_senderMac;
		}

		Ptr<Packet> SenderTag::GetSenderPacket() const
		{
			return m_senderPacket;
		}


		void SenderTag::Print(std::ostream &os) const
		{
			os << "sender=" << m_senderMac << "senderP=" << m_senderPacket;
		}
	} // namespace HrWpan

}// namespace ns3