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
#include "hr-wpan-devid-helper.h"

#include <ns3/hr-wpan-dev-id.h>

namespace ns3
{
	namespace HrWpan
	{

		DevIdHelper::DevIdHelper()
		{
			chars[0] = 0x30;
			chars[1] = 0x30;
		}

		void DevIdHelper::Install(NetDeviceContainer ndc)
		{
			for (NetDeviceContainer::Iterator i = ndc.Begin(); i != ndc.End(); ++i)
			{
				incrementAddress();
				(*i)->SetAddress(HrWpanDevId(getAddress()));
				
			}
		}

		void DevIdHelper::incrementAddress()
		{
			chars[1]++;

			if (chars[1] == 0x3A)
			{
				chars[0]++;
				chars[1] = 0x30;
			}
		}

		char * DevIdHelper::getAddress() const
		{
			return (char*) chars;
		}

	} //namespace HrWpan

} // namespace ns3