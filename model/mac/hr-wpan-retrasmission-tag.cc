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

#include "hr-wpan-retrasmission-tag.h"
#include <ns3/integer.h>

namespace ns3
{
	namespace HrWpan
	{
		TypeId	RetrasmissionTag::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpan::RetrasmissionTag")
				.SetParent<Tag>()
				.AddConstructor<RetrasmissionTag>()
				.AddAttribute("Counter",
				"Retrasmission attempt counter!",
				EmptyAttributeValue(),
				MakeIntegerAccessor(&RetrasmissionTag::m_counter),
				MakeIntegerChecker());
			return tid;
		}

		TypeId	TimestampTag::GetInstanceTypeId(void) const
		{
			return GetTypeId();
		}

		uint32_t TimestampTag::GetSerializedSize(void) const
		{
			return 8;
		}

		void TimestampTag::Serialize(TagBuffer i) const
		{
			int64_t t = m_timestamp.GetNanoSeconds();
			i.Write((const uint8_t *)&t, 8);
		}

		void TimestampTag::Deserialize(TagBuffer i)
		{
			int64_t t;
			i.Read((uint8_t *)&t, 8);
			m_timestamp = NanoSeconds(t);
		}

		void TimestampTag::SetTimestamp(Time time)
		{
			m_timestamp = time;
		}
		Time TimestampTag::GetTimestamp(void) const
		{
			return m_timestamp;
		}

		void TimestampTag::Print(std::ostream &os) const
		{
			os << "t=" << m_timestamp;
		}
	} // namespace HrWpan

}// namespace ns3