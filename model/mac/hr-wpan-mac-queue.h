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

#ifndef HR_WPAN_MAC_QUEUE_H
#define HR_WPAN_MAC_QUEUE_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-mac-header.h>
#include <ns3/nstime.h>
#include <ns3/queue.h>

namespace ns3
{
	class HrWpanMacQueue : public Object
	{

	public:
		HrWpanMacQueue();
		virtual ~HrWpanMacQueue();

		void SetMaxSize(uint32_t maxSize);
		void Enqueue(Ptr<const Packet> packet, const HrWpan::MacHeader & hdr);

		Ptr<const Packet> Dequeue(HrWpan::MacHeader * hdr);

	protected:

		void CleanUp(void);

		struct Item
		{
			/**
			* Create a struct with the given parameters.
			*
			* \param packet
			* \param hdr
			* \param tstamp
			*/
			Item(Ptr<const Packet> packet,
				const HrWpan::MacHeader &hdr,
				Time tstamp);
			Ptr<const Packet> packet; //!< Actual packet
			HrWpan::MacHeader hdr; //!< Wifi MAC header associated with the packet
			Time tstamp; //!< timestamp when the packet arrived at the queue
		};

		typedef std::list<struct Item> PacketQueue;
		/**
		* typedef for packet (struct Item) queue reverse iterator.
		*/
		typedef std::list<struct Item>::reverse_iterator PacketQueueRI;
		/**
		* typedef for packet (struct Item) queue iterator.
		*/
		typedef std::list<struct Item>::iterator PacketQueueI;

		PacketQueue m_packetQueue;
		uint32_t m_maxSize;

	};

} //namespace ns3

#endif //HR_WPAN_MAC_QUEUE_H