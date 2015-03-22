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


	void HrWpanMacQueue::Enqueue(Ptr<const Packet> packet,const HrWpan::MacHeader & hdr)
	{
		NS_LOG_FUNCTION(this <<packet << hdr);

	}

}

