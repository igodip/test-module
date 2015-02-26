///////////////////////////////////////////////////////////
//  hr-wpan-mac-queue.cpp
//  Implementation of the Class HrWpanMacQueue
//  Created on:      26-feb-2015 13:35:38
//  Original author: Igor
///////////////////////////////////////////////////////////

#include "hr-wpan-mac-queue.h"
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanMacQueue");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanMacQueue);

	HrWpanMacQueue::HrWpanMacQueue()
	{
		NS_LOG_FUNCTION(this);
	}

	HrWpanMacQueue::~HrWpanMacQueue()
	{
		NS_LOG_FUNCTION(this);
	}

	void HrWpanMacQueue::SetMaxSize(uint32_t maxSize)
	{
		NS_LOG_FUNCTION(this << maxSize);
		m_maxSize = maxSize;
	}


	void HrWpanMacQueue::Enqueue(Ptr<const Packet> packet,const HrWpanMacHeader & hdr)
	{
		NS_LOG_FUNCTION(this <<packet << hdr);

	}

}

