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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-ctrl-packet-factory.h"
#include <ns3/packet.h>
#include <ns3/log.h>
#include <ns3/hr-wpan-dev-id.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanCtrlPacketFactory");

	Ptr<Packet> HrWpanCtrlPacketFactory::CreateRtsPacket(HrWpan::DevId sender, HrWpan::DevId receiver, Time duration)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[14];
		
		buffer[0] = 0x01; //RTS
		buffer[1] = 0x00;
		sender.CopyTo(buffer+2);
		receiver.CopyTo(buffer+4);
		memcpy(buffer+6, ((uint8_t*) &duration), 8);

		Ptr<Packet> p = Create<Packet>(buffer,14);

		NS_LOG_INFO(duration);
		

		return p;
	}

	Ptr<Packet> HrWpanCtrlPacketFactory::CreateCtsPacket(HrWpan::DevId receiver, Time duration)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[12];
		buffer[0] = 0x00; //CTS
		buffer[1] = 0x02;

		receiver.CopyTo(buffer+2);
		memcpy(buffer + 4, &duration, 8);

		Ptr<Packet> p = Create<Packet>(buffer, 12);

		return p;
	}

	void HrWpanCtrlPacketFactory::ParseRtsPacket(Ptr<Packet> p, HrWpan::DevId & sender, HrWpan::DevId & receiver, Time & duration)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[12];
		buffer[0] = 0x00; //CTS
		buffer[1] = 0x02;

		p->CopyData(buffer, 12);

		sender.CopyFrom(buffer+2);
		receiver.CopyFrom(buffer + 4);
		memcpy(&duration, buffer + 6, 8);

	}

	void HrWpanCtrlPacketFactory::ParseCtsPacket(Ptr<Packet> p, HrWpan::DevId & receiver, Time & duration)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[12];

		if (p->CopyData(buffer, 12) != 12)
		{
			NS_LOG_ERROR("Packet not Cts");
			return;
		}

		receiver.CopyFrom(buffer + 2);
		memcpy(&duration, buffer + 4, 8);

	}

	HrWpanCtrlPacketFactory::HrWpanCtrlPacketFactory()
	{
		NS_LOG_FUNCTION(this);

	}

	HrWpanCtrlPacketFactory::~HrWpanCtrlPacketFactory()
	{
		NS_LOG_FUNCTION(this);

	}

	HrWpanCtrlPacketFactory & HrWpanCtrlPacketFactory::getInstance()
	{
		static HrWpanCtrlPacketFactory factory;

		return factory;
	}

	void HrWpanCtrlPacketFactory::ParseAckPacket(Ptr<Packet> p, HrWpan::DevId & sender, uint32_t packetId)
	{
		NS_LOG_FUNCTION(this);
	}

	Ptr<Packet> HrWpanCtrlPacketFactory::CreateAckPacket(HrWpan::DevId sender, uint32_t packetId)
	{
		NS_LOG_FUNCTION(this);

		Ptr<Packet> p = Create<Packet>();

		return p;
	}

}