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

#include "hr-wpan-mac.h"
#include <ns3/log.h>

namespace ns3 {
	
	NS_LOG_COMPONENT_DEFINE("HrWpanMac");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanMac);

	HrWpanMac::HrWpanMac()
	{
		NS_LOG_FUNCTION(this);
	}

	TypeId HrWpanMac::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::HrWpanMac")
			.SetParent<Object>()
			.AddConstructor<HrWpanMac>();

		return tid;
	}

	void HrWpanMac::AckWaitTimeout(void)
	{
		NS_LOG_FUNCTION(this);

	}

	void HrWpanMac::PrepareRetransmission(void)
	{
		NS_LOG_FUNCTION(this);

	}

	void HrWpanMac::DoDispose()
	{
		NS_LOG_FUNCTION(this);

		Object::DoDispose();
	}

	void HrWpanMac::AssociatePhyProvider(HrWpanPhyProvider* hrWpanPhyProvider)
	{
		NS_LOG_FUNCTION(this << hrWpanPhyProvider);

		m_phyProvider = hrWpanPhyProvider;

	}

	void HrWpanMac::ReceivePhyPdu(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		//Lancio il pacchetto cosi' a secco! :D
		// 
		//m_phyProvider->SendMacPdu(p);
		//moveTrailer(trailer);
		
		//Check if it's for me

	}

	void HrWpanMac::ReceivePhyControlMessage(Ptr<HrWpanPhyControlMessage> cMsg)
	{
		NS_LOG_FUNCTION(this << cMsg);
		
	}

	void HrWpanMac::DoInitialize(void)
	{
		NS_LOG_FUNCTION(this);

		Object::DoInitialize();
	}

	HrWpanMac * HrWpanMac::GetPointer(void) const
	{
		NS_LOG_FUNCTION(this);

		return (HrWpanMac *)this;
	}

	void HrWpanMac::SetPhyProvider(HrWpanPhyProvider * provider)
	{
		NS_LOG_FUNCTION(this << provider);

		m_phyProvider = provider;

	}

	HrWpanPhyProvider * HrWpanMac::GetPhyProvider(void) const
	{
		NS_LOG_FUNCTION(this);

		return m_phyProvider;
	}

	void HrWpanMac::McpsDataRequest(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this<<packet);

		m_phyProvider->SendMacPdu(packet);
	}

	void HrWpanMac::SetDevId(HrWpanDevId devId)
	{
		m_devId = devId;
	}

	HrWpanDevId HrWpanMac::GetDevId(void) const
	{
		NS_LOG_FUNCTION(this);
		return m_devId;
	}

	void HrWpanMac::RegisterSapUser(HrWpan::MacSapUser * macSapUser)
	{
		NS_LOG_FUNCTION(this << macSapUser);
		m_sapUsers[macSapUser->GetName()] = macSapUser;

	}

} //namespace ns3