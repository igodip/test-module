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
 * Igor Di Paolo <igor.di.paolo@gmail.com>
 */
#include "hr-wpan-mac-trailer.h"
#include <ns3/packet.h>
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanMacTrailer");

	namespace HrWpan
	{
		NS_OBJECT_ENSURE_REGISTERED(MacTrailer);

		const uint16_t MacTrailer::HR_WPAN_MAC_FCS_LENGTH = 4;

		MacTrailer::MacTrailer(void)
			: m_fcs(0),
			m_calcFcs(false)
		{
			NS_LOG_FUNCTION(this);
		}

		TypeId MacTrailer::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpanMacTrailer")
				.SetParent<Trailer>()
				.AddConstructor<MacTrailer>();
			return tid;
		}

		TypeId MacTrailer::GetInstanceTypeId(void) const
		{
			return GetTypeId();
		}

		void MacTrailer::Print(std::ostream &os) const
		{
			os << " FCS = " << m_fcs;
		}

		uint32_t MacTrailer::GetSerializedSize(void) const
		{

			NS_LOG_FUNCTION(this);

			return HR_WPAN_MAC_FCS_LENGTH;
		}

		void MacTrailer::Serialize(Buffer::Iterator start) const
		{
			NS_LOG_FUNCTION(this);
			start.Prev(HR_WPAN_MAC_FCS_LENGTH);
			start.WriteU32(m_fcs);
		}

		uint32_t MacTrailer::Deserialize(Buffer::Iterator start)
		{
			NS_LOG_FUNCTION(this);

			start.Prev(HR_WPAN_MAC_FCS_LENGTH);
			m_fcs = start.ReadU32();

			return HR_WPAN_MAC_FCS_LENGTH;
		}

		uint32_t MacTrailer::GetFcs(void) const
		{

			NS_LOG_FUNCTION(this);

			return m_fcs;
		}

		void MacTrailer::SetFcs(Ptr<const Packet> p)
		{

			NS_LOG_FUNCTION(this << p);

			if (m_calcFcs)
			{
				uint16_t size = p->GetSize();
				uint8_t *serial_packet = new uint8_t[size];

				p->CopyData(serial_packet, size);

				m_fcs = GenerateCrc32(serial_packet, size);
				delete[] serial_packet;
			}
		}

		/* Be sure to have removed the trailer and only the trailer
		* from the packet before to use CheckFcs */
		bool MacTrailer::CheckFcs(Ptr<const Packet> p)
		{

			NS_LOG_FUNCTION(this << p);

			if (!m_calcFcs)
			{
				return true;
			}
			else
			{
				uint16_t checkFcs;
				uint16_t size = p->GetSize();
				uint8_t *serial_packet = new uint8_t[size];

				p->CopyData(serial_packet, size);

				checkFcs = GenerateCrc32(serial_packet, size);
				delete[] serial_packet;
				return (checkFcs == GetFcs());
			}
		}

		void MacTrailer::EnableFcs(bool enable)
		{

			NS_LOG_FUNCTION(this << enable);

			m_calcFcs = enable;
			if (!enable)
			{
				m_fcs = 0;
			}
		}

		bool MacTrailer::IsFcsEnabled(void)
		{
			NS_LOG_FUNCTION(this);

			return m_calcFcs;
		}

		/**
		* This CRC32 algorithm has no table lookup
		*/
		uint32_t MacTrailer::GenerateCrc32(uint8_t *data, int length)
		{

			NS_LOG_FUNCTION(this << *data << length);

			int i, j;
			uint32_t byte, crc, mask;

			i = 0;
			crc = 0xFFFFFFFF;
			for (i = 0; i < length; ++i)
			{
				byte = *data;
				crc = crc ^ byte;
				for (j = 7; j >= 0; j--) {    // Do eight times.
					mask = -(crc & 1);
					crc = (crc >> 1) ^ (0xEDB88320 & mask);
				}
				i = i + 1;
				++data;
			}
			return ~crc;
		}

		bool MacTrailer::operator== (const MacTrailer & macTrailer) const
		{
			NS_LOG_FUNCTION(this << macTrailer);

			return (m_fcs == macTrailer.m_fcs) && (m_calcFcs == macTrailer.m_fcs);
		}

	} // namespace HrWpan

} //namespace ns3
