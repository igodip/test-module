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

#ifndef HR_WPAN_MAC_SUBHEADER_SH_H
#define HR_WPAN_MAC_SUBHEADER_SH_H

#include <ns3/header.h>

namespace ns3 {

	class HrWpanMacSubheaderSh : Header {
	public:
		uint8_t m_MSC_information;			//5bit
		uint8_t m_FCS_present;				//1bit
		uint8_t m_retry;					//1bit
		uint8_t m_resolution_indication;	//1bit
		uint8_t m_subframe_length;			//11bit
		uint8_t m_subframe_information;		//2bit
		uint8_t m_skrewed_constellation;	//1bit
		uint8_t m_MSDU_number;				//9bit
		uint8_t m_fragment_number;			//7bit
		uint8_t m_last_fragment;			//1bit
		uint8_t m_reserved;					//1bit
	};

}

#endif
