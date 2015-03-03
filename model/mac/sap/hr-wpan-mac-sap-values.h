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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/
#ifndef HR_WPAN_MAC_SAP_VALUES
#define HR_WPAN_MAC_SAP_VALUES

#include <ns3/data-rate.h>

namespace ns3
{
	namespace HrWpan
	{

		namespace Mac
		{

			typedef uint16_t RequestId;
			typedef uint8_t StreamIndex;
			typedef uint8_t ReliabilityExponent;
			typedef uint16_t TransmitTimeout;
			typedef uint8_t MaxRetries;
			typedef bool SECMode;
			typedef uint8_t UserPriority;
			typedef bool ACKRequested;
			
			enum ConfirmRequested
			{
				NEVER = 0,
				ALWAYS = 1,
				ON_ERROR = 2
			};

			typedef bool SNAPHeaderPresent;
			typedef uint8_t Length; //The length of the MSDU in octets.
			
			typedef uint32_t TransmitDelay;

			enum ResultCode 
			{
				SUCCESS = 0,
				FAILURE = 1
			};

			enum ReasonCode
			{
				REQUEST_TIMEOUT = 0,
				TARGET_UNAVAILABLE,
				RESOURCES_UNAVAILABLE,
				TERMINATED_BY_PNC,
				TERMINATED_BY_DEST,
				TRANSMIT_DELAY_UNSUPPORTED,
				PNC_BUSY,
				DEV_IN_PS_MODE,
				NOT_ASSOCIATED,
				UNKNOWN_STREAM,
				OTHER
			};

			//struct 
				

		} // namespace Mac


	} //namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_MAC_SAP_VALUES