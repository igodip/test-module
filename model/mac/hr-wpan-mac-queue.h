///////////////////////////////////////////////////////////
//  hr-wpan-mac-queue.h
//  Implementation of the Class HrWpanMacQueue
//  Created on:      26-feb-2015 13:35:38
//  Original author: Igor
///////////////////////////////////////////////////////////

#ifndef HR_WPAN_MAC_QUEUE_H
#define HR_WPAN_MAC_QUEUE_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-mac-header.h>
#include <ns3/nstime.h>

namespace ns3
{
	class HrWpanMacQueue : public Object
	{

	public:
		HrWpanMacQueue();
		virtual ~HrWpanMacQueue();

		void SetMaxSize(uint32_t maxSize);
		void Enqueue(Ptr<const Packet> packet, const HrWpanMacHeader & hdr);

		Ptr<const Packet> Dequeue(HrWpanMacHeader * hdr);

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
				const HrWpanMacHeader &hdr,
				Time tstamp);
			Ptr<const Packet> packet; //!< Actual packet
			HrWpanMacHeader hdr; //!< Wifi MAC header associated with the packet
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