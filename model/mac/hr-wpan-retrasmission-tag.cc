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
				MakeIntegerChecker<uint8_t>());
			return tid;
		}

		TypeId	RetrasmissionTag::GetInstanceTypeId(void) const
		{
			return GetTypeId();
		}

		uint32_t RetrasmissionTag::GetSerializedSize(void) const
		{
			return 1;
		}

		void RetrasmissionTag::Serialize(TagBuffer i) const
		{
			i.WriteU8(m_counter);
		}

		void RetrasmissionTag::Deserialize(TagBuffer i)
		{
			m_counter = i.ReadU8();	
		}

		void RetrasmissionTag::IncCounter()
		{
			m_counter++;
		}
		uint8_t RetrasmissionTag::GetCounter(void) const
		{
			return m_counter;
		}

		void RetrasmissionTag::Print(std::ostream &os) const
		{
			os << "rt=" << m_counter;
		}
	} // namespace HrWpan

}// namespace ns3