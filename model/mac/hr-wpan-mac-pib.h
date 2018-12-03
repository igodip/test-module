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

#ifndef HR_WPAN_MAC_PIB_H
#define HR_WPAN_MAC_PIB_H

#include <ns3/log.h>
#include <ns3/mac48-address.h>
#include <ns3/hr-wpan-dev-id.h>

namespace ns3
{
	namespace HrWpan
	{

		struct MacPib
		{
			//PNC Values

			uint16_t CAPEndTime;
			uint16_t SuperframeDuration;
			uint8_t PNCCapable; //1 can be PNC , 0 only DEV
			uint8_t PNCDesMode; //1 if ti is desired that the Dev be the PNC
			uint8_t MaxPSSets; // The maximum number of PS sets supported by the PNC
			// MACPIB BSID
			uint16_t MaxAssociatedDEVs;
			uint16_t MaxCTRqBs;
			uint8_t Sec;
			uint8_t PNCServicesBroadcast; //0x00 PNC sends information about its services

			//Other values
			Mac48Address DEVAddress;
			HrWpanDevId DEVID;
			uint8_t PowerManagementMode;
			uint8_t PSPSSupported;
			uint8_t DSPSSupported;
			uint8_t APSSupported;
			uint8_t MaxStreams;
			uint8_t PowerSource;
			uint8_t SecurityOptionImplemented;
			uint8_t DEVServicesBroadcast;


		};

	}  //hrWpan  namespace

} //ns3 namespace

#endif