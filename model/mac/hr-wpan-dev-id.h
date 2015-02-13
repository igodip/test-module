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
		/**
		* 
		*/
		HrWpanDevId(void);
		/**
		* \param str a string representing the new Mac16Address
		*/
		HrWpanDevId(const char * str);
		/**
		* Copy the buffer in our internal buffer
		*
		* \param buffer address in network order
		*/
		void CopyFrom(const uint8_t & buffer);
		/**
		* Copy the internal address to the input buffer
		*
		* \param buffer address in network order
		*/
		void CopyTo(uint8_t & buffer) const; 
		/**
		* Convert in instance of this class to a polymorphic Address instance
		*
		* \returns a new Address instance
		*/
		operator Address() const;
		/**
		* This function perform a tye check and asserts if the
		* type of the input address is not compatible with an
		* HrWpanDevId
		*
		* \param address address to test
		* \returns true if the address matches, false otherwise.
		*/
		static HrWpanDevId convertFrom(const Address & address);
		/**
		* \param address address to test
		* \returns true if the address matches, false otherwise
		*/
		static bool isMatchingType(const Address & address);
		/**
		* Allocate a new HrWpanDevId.
		*
		* \returns newly allocated HrWpanIdAddress.
		*/
		static HrWpanDevId Allocate(void);

	private:
		/**
		* \returns a new Address instance
		*
		* Convert an instance of this class to a polymorphic Address instance.
		*/
		Address convertTo(void) const;
		/**
		* \brief Return the Type of address
		* \return type of address
		*/
		static uint8_t GetType(void);
		/**
		* \brief Equal to operator
		*
		* \param a the first operand
		* \param b the second operand
		* \returns true if the operands are equal
		*/
		friend bool operator == (const HrWpanDevId &a, const HrWpanDevId &b);
		/**
		* \brief Not equal to operator
		*
		* \param a the first operand
		* \param b the second operand
		* \returns true if the operands are equal
		*/
		friend bool operator != (const HrWpanDevId &a, const HrWpanDevId &b);
		/**
		* \brief Equal to operator
		*
		* \param a the first operand
		* \param b the second operand
		* \returns true if the operands are equal
		*/
		friend bool operator < (const HrWpanDevId &a, const HrWpanDevId &b);
		/**
		* \brief Stream insertion operator
		*
		* \param os the stream
		* \param address the address
		* \returns a reference to the stream
		*/
		friend std::ostream& operator <<(std::ostream & os, const HrWpanDevId & address);
		/**
		* \brief Stream extraction operator
		*
		* \param is the stream
		* \param address the address
		* \returns a reference to the stream
		*/
		friend std::istream& operator >>(std::istream & is,  HrWpanDevId & address);

		uint8_t m_address; //!< address value
	};

	inline bool operator == (const HrWpanDevId &a, const HrWpanDevId &b)
	{
		return (a.m_address == b.m_address);
	}

	inline bool operator != (const HrWpanDevId &a, const HrWpanDevId &b)
	{
		return (a.m_address != b.m_address);
	}

	inline bool operator < (const HrWpanDevId &a, const HrWpanDevId & b)
	{
		return (a.m_address < b.m_address);
	}

	std::ostream& operator<<(std::ostream & os, const HrWpanDevId);
	std::istream& operator>>(std::istream & is, HrWpanDevId & address);

} // namespace ns3

#endif /* HR_WPAN_DEV_ID_H */