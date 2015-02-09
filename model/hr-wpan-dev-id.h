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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#ifndef HR_WPAN_DEV_ID
#define HR_WPAN_DEV_ID

#include <stdint.h>
#include <ostream>
#include <ns3/address.h>

namespace ns3 {

	class Address;

	class HrWpanDevId {
	public:
		HrWpanDevId(void);
		/**
		 *
		*/
		HrWpanDevId(const char * str);
		

		void CopyFrom(const uint8_t buffer);

		void CopyTo(uint8_t buffer) const; //TODO: Errato al massimo livello

		operator Address() const;

		static HrWpanDevId convertFrom(const Address & address);

		static bool isMatchingType(const Address & address);

		static HrWpanDevId Allocate(void);

	private:
		Address convertTo(void) const;

		static uint8_t GetType(void);
		
		friend bool operator == (const HrWpanDevId &a, const HrWpanDevId &b);

		friend bool operator != (const HrWpanDevId &a, const HrWpanDevId &b);

		//friend bool operator

	};
}

#endif