/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2015
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

#include "hr-wpan-phy.h"
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanPhy");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhy);
	
	HrWpanPhy::HrWpanPhy()
	{

	}

	TypeId HrWpanPhy::GetTypeId(void) 
	{
		static TypeId tid = TypeId("ns3::HrWpanPhy")
			.SetParent<Object>()
			.AddConstructor<HrWpanPhy>()
			;

		return tid;
	}

	void HrWpanPhy::DoDispose(void) 
	{

		NS_LOG_FUNCTION(this);

		SpectrumPhy::DoDispose();
	
	}

	Ptr<NetDevice> HrWpanPhy::GetDevice()  
	{
		
		NS_LOG_FUNCTION(this);

		return m_netdevice;
	}

	void HrWpanPhy::SetDevice(Ptr<NetDevice> netDevice) 
	{

		NS_LOG_FUNCTION(this << netDevice);

		m_netdevice = netDevice;
	}

	void HrWpanPhy::SetChannel(Ptr<SpectrumChannel> c)
	{
		NS_LOG_FUNCTION(c);
	}

}
