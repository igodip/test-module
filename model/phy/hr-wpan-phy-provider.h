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

#ifndef HR_WPAN_PHY_PROVIDER_H
#define HR_WPAN_PHY_PROVIDER_H

#include <ns3/packet.h>
#include <ns3/hr-wpan-phy-control-message.h>

namespace ns3
{
	class HrWpanPhyProvider {

	public:
		//virtual 
		virtual void SendMacPdu(Ptr<Packet> p) = 0;

		/**
		* \brief Send SendLteControlMessage (PDCCH map, CQI feedbacks) using the ideal control channel
		* \param msg the Ideal Control Message to send
		*/
		virtual void SendHrWpanControlMessage(Ptr<HrWpanPhyControlMessage> msg) = 0;
		/* Clear channel assessment*/
		virtual bool IsChannelIdle() = 0;

		//Rx methods
		virtual bool IsRxOn() const = 0;
		virtual void RxOn() = 0;

		//Tx methods
		virtual bool IsTxOn() const = 0;
		virtual void TxOn() = 0;
	};
}

#endif