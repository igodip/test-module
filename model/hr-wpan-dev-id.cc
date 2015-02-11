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

#include "hr-wpan-dev-id.h"
#include "ns3/address.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include <iomanip>
#include <iostream>
#include <cstring>

namespace ns3{

	NS_LOG_COMPONENT_DEFINE("HrWpanDevId");

	ATTRIBUTE_HELPER_CPP(HrWpanDevId);

#define ASCII_a (0x41)
#define ASCII_z (0x5a)
#define ASCII_A (0x61)
#define ASCII_Z (0x7a)
#define ASCII_COLON (0x3a)
#define ASCII_ZERO (0x30)

	/**
	* Converts a char to lower case.
	* \param c the char
	* \returns the lower case
	*/
	static char
		AsciiToLowCase(char c)
	{
		if (c >= ASCII_a && c <= ASCII_z) {
			return c;
		}
		else if (c >= ASCII_A && c <= ASCII_Z) {
			return c + (ASCII_a - ASCII_A);
		}
		else {
			return c;
		}
	}

	HrWpanDevId::HrWpanDevId(void){
		NS_LOG_FUNCTION(this);
		m_address = 0;
	}

	HrWpanDevId::HrWpanDevId(const char* str){
		NS_LOG_FUNCTION(this << str);

		uint8_t byte = 0;
		while (*str != ASCII_COLON && *str != 0)
		{
			byte <<= 4;
			char low = AsciiToLowCase(*str);
			if (low >= ASCII_a)
			{
				byte |= low - ASCII_a + 10;
			}
			else
			{
				byte |= low - ASCII_ZERO;
			}
			str++;
		}

		m_address = byte;

	}

	void HrWpanDevId::CopyFrom(const uint8_t & buffer)
	{
		NS_LOG_FUNCTION(this << buffer);
		m_address = buffer;
	}

	void HrWpanDevId::CopyTo(uint8_t & buffer) const
	{
		NS_LOG_FUNCTION(this << buffer);
		buffer = m_address;
	}

	bool HrWpanDevId::isMatchingType(const Address & address)
	{
		NS_LOG_FUNCTION(&address);
		return address.CheckCompatible(GetType(), 1);
	}

	HrWpanDevId::operator Address () const
	{
		return convertTo();
	}

	HrWpanDevId HrWpanDevId::convertFrom(const Address & address)
	{
		NS_LOG_FUNCTION(address);
		NS_ASSERT(address.CheckCompatible(GetType(), 1));
		HrWpanDevId retval;
		address.CopyTo(&(retval.m_address));
		return retval;
	}

	Address HrWpanDevId::convertTo(void) const
	{
		NS_LOG_FUNCTION(this);
		return Address(GetType(), &m_address, 1);
	}

	HrWpanDevId HrWpanDevId::Allocate(void){
		NS_LOG_FUNCTION_NOARGS();
		static uint64_t id = 0;
		id++;
		HrWpanDevId address;
		address.m_address = id & 0xFF;
		return address;
	}

	uint8_t HrWpanDevId::GetType(void)
	{
		NS_LOG_FUNCTION_NOARGS();
		static uint8_t type = Address::Register();
		return type;
	}

	std::ostream & operator << (std::ostream & os, const HrWpanDevId & address)
	{
		uint8_t ad;
		address.CopyTo(ad);

		os.setf(std::ios::hex, std::ios::basefield);
		os.fill('0');

		os << std::setw(2) << (uint32_t)ad;

		os.setf(std::ios::dec, std::ios::basefield);
		os.fill(' ');
		return os;
	}

	std::istream & operator>>(std::istream & is, HrWpanDevId & address)
	{

		std::string v;
		is >> v;

		std::string::size_type col = 0;

		std::string tmp;
		std::string::size_type next;
		next = v.find(":", col);
		if (next == std::string::npos)
		{
			tmp = v.substr(col, v.size() - col);
			address.m_address = strtoul(tmp.c_str(), 0, 16);
			
		}
		else
		{
			tmp = v.substr(col, next - col);
			address.m_address = strtoul(tmp.c_str(), 0, 16);
			col = next + 1;
		}

	}
}