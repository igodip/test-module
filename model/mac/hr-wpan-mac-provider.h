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

#ifndef HR_WPAN_MAC_PROVIDER_H
#define HR_WPAN_MAC_PROVIDER_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/hr-wpan-mac-header.h>

namespace ns3
{
	class HrWpanMacProvider
	{
	public:
		
		struct TrasnmitPduAsyncParameters
		{
			Ptr<Packet> pdu;
			
		};

		virtual void TransmitPduAsync(const TrasnmitPduAsyncParameters & params) = 0;

		struct TransmitPduIsochParameters
		{
			//RequestID
			// StreamIndex
			// TransmitTimeout
			// MaxRetries
			// SNAPHeaderPresent
			// ACKRequested
			// ConfirmRequested
			// Length
			// Data
			// DataType
			// UEPAllowed
			// InterlacedFieldIndication
			// VideoFrameNumber
			// HPosition
			// VPosition
			HrWpanDevId trgtId;
			HrWpanDevId origId;
		};

		virtual void TransmitPduIsoch(const TransmitPduIsochParameters & params) = 0;
	};
}

#endif