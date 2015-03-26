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

#include "hr-wpan-mac-manager-sync.h"

#include <ns3/hr-wpan-net-device.h>
#include <ns3/log.h>

namespace ns3
{
	namespace HrWpan
	{

		MacManagerSync::MacManagerSync()
		{

		}

		void MacManagerSync::AddListener(MacManagerListener * listener)
		{
			m_listeners.push_back(listener);
		}

		void MacManagerSync::AddListeners(NetDeviceContainer ndc)
		{
			NetDeviceContainer::Iterator i = ndc.Begin();

			for (; i != ndc.End(); ++i)
			{
				Ptr<HrWpan::HrWpanNetDevice> netDevice = DynamicCast<HrWpan::HrWpanNetDevice>(*i);
				
				if (netDevice != 0)
				{
					AddListener(netDevice->GetMac()->GetPointer());
				}

			}

		}

		TypeId MacManagerSync::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpan::MacManagerSync").
				SetParent<Object>().
				AddConstructor<MacManagerSync>();

			return tid;
		}

		void MacManagerSync::Activate()
		{

		}

	} // namespace HrWpan

} // namespace ns3
