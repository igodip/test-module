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


#ifndef HR_WPAN_MAC_MANAGER_SYNC_H
#define HR_WPAN_MAC_MANAGER_SYNC_H

#include <ns3/simulator.h>
#include <ns3/net-device-container.h>

#include <list>

#include "hr-wpan-mac-manager-listener.h"

namespace ns3
{
	namespace HrWpan
	{

		class MacManagerSync : public Object
		{

		public:

			MacManagerSync();

			void AddListener(MacManagerListener *);
			void AddListeners(NetDeviceContainer ndc);
			virtual void Activate() = 0;

			static TypeId GetTypeId(void);

		protected:

			std::list < MacManagerListener * > m_listeners;

		};

	} // namespace HrWpan

} // namespace ns3

#endif //HR_WPAN_MAC_MANAGER_SYNC
