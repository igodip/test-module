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
#include <cstring>

namespace ns3 {

	class Address;

	namespace HrWpan
	{
		class DevId {
		public:
			/**
			*
			*/
			DevId(void);
			/**
			* \param str a string representing the new Mac16Address
			*/
			DevId(const char * str);
			/**
			* Copy the buffer in our internal buffer
			*
			* \param buffer address in network order
			*/
			void CopyFrom(const uint8_t buffer[2]);
			/**
			* Copy the internal address to the input buffer
			*
			* \param buffer address in network order
			*/
			void CopyTo(uint8_t buffer[2]) const;
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
			static DevId convertFrom(const Address & address);
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
			static DevId Allocate(void);
			/*
			*/
			static DevId GetBroadcast(void);
			/**
			*
			*/
			bool IsBroadcast() const;

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
			friend bool operator == (const DevId &a, const DevId &b);
			/**
			* \brief Not equal to operator
			*
			* \param a the first operand
			* \param b the second operand
			* \returns true if the operands are equal
			*/
			friend bool operator != (const DevId &a, const DevId &b);
			/**
			* \brief Equal to operator
			*
			* \param a the first operand
			* \param b the second operand
			* \returns true if the operands are equal
			*/
			friend bool operator < (const DevId &a, const DevId &b);
			/**
			* \brief Stream insertion operator
			*
			* \param os the stream
			* \param address the address
			* \returns a reference to the stream
			*/
			friend std::ostream& operator <<(std::ostream & os, const DevId & address);
			/**
			* \brief Stream extraction operator
			*
			* \param is the stream
			* \param address the address
			* \returns a reference to the stream
			*/
			friend std::istream& operator >>(std::istream & is, DevId & address);

			uint8_t m_address[2]; //!< address value
		};

		inline bool operator == (const DevId &a, const DevId &b)
		{
			return memcmp(a.m_address, b.m_address, 2) == 0;
		}

		inline bool operator != (const DevId &a, const DevId &b)
		{
			return memcmp(a.m_address, b.m_address, 2) != 0;
		}

		inline bool operator < (const DevId &a, const DevId & b)
		{
			return memcmp(a.m_address, b.m_address, 2) < 0;
		}

		std::ostream& operator<<(std::ostream & os, const DevId & address);
		std::istream& operator>>(std::istream & is, DevId & address);
	}


} // namespace ns3

#endif /* HR_WPAN_DEV_ID_H */