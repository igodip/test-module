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

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/singleton.h>
#include <ns3/nstime.h>
#include <ns3/address.h>
#include <ns3/hr-wpan-dev-id.h>
#include <complex>
#include <ns3/double.h>
#include <ns3/hr-wpan-mac-header.h>


namespace ns3
{
	class HrWpanCtrlPacketFactory 
	{
	public:

		static HrWpanCtrlPacketFactory & getInstance();

		//Ptr<Packet> CreateRtsPacket(HrWpan::DevId sender, HrWpan::DevId receiver, Time duration);
                Ptr<Packet> CreateRtsPacket(std::vector<std::complex<double> > rtsCssSequence, Time duration);
		Ptr<Packet> CreateCtsPacket(HrWpan::DevId receiver, Time duration);

		void ParseRtsPacket(Ptr<Packet> p,HrWpan::DevId & sender,HrWpan::DevId & receiver, Time & duration);
		void ParseCtsPacket(Ptr<Packet> p, HrWpan::DevId & receiver, Time & duration);
		void ParseAckPacket(Ptr<Packet> p, HrWpan::DevId & sender, uint32_t packetId);

		Ptr<Packet> CreateAckPacket(HrWpan::DevId sender, uint32_t packetId);
                HrWpan::MacHeader CreateRtsHeader(std::vector<std::complex<double> > rtsCssSequence, Time duration);


	protected:

	private:

		HrWpanCtrlPacketFactory();
		~HrWpanCtrlPacketFactory();
	};
}
