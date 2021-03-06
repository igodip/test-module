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

#ifndef HR_WPAN_TIMESTAMPTAG_H
#define HR_WPAN_TIMESTAMPTAG_H

#include <ns3/object.h>
#include <ns3/tag.h>
#include <ns3/nstime.h>

namespace ns3
{
	
	class TimestampTag : public Tag {
	public:
		static TypeId GetTypeId(void);
		virtual TypeId GetInstanceTypeId(void) const;

		virtual uint32_t GetSerializedSize(void) const;
		virtual void Serialize(TagBuffer i) const;
		virtual void Deserialize(TagBuffer i);

		// these are our accessors to our tag structure
		void SetTimestamp(Time time);
		Time GetTimestamp(void) const;

		void Print(std::ostream &os) const;

	private:
		Time m_timestamp;


	};

}

#endif