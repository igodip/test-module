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
* Author:  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include <ns3/test.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-mac-header.h>
#include <ns3/hr-wpan-mac-trailer.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/mac64-address.h>
#include <ns3/log.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("hr-wpan-packet-test");

// This is an example TestCase.
class HrWpanPacketTestCase : public TestCase {
public:
	HrWpanPacketTestCase();
	virtual ~HrWpanPacketTestCase();
private:
	virtual void DoRun(void);
};

HrWpanPacketTestCase::HrWpanPacketTestCase()
	: TestCase("Test the 802.15.3c MAC header and trailer classes")
{}

HrWpanPacketTestCase::~HrWpanPacketTestCase()
{
}

void
HrWpanPacketTestCase::DoRun(void)
{
	
	const char * addr = "11";

	HrWpanMacHeader macHdr(HrWpanMacHeader::HRWPAN_FRAME_BEACON, 0);
	macHdr.SetSecDisable();
	
	HrWpanDevId srcAddress(addr);
	macHdr.setSrcAddress(srcAddress);

	HrWpanMacTrailer macTrailer;
	
	Ptr<Packet> packet = Create<Packet>(20); // dummy data
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(),20, "Packed created with unexpected size!");

	packet->AddHeader(macHdr); //+10 bytes fixed
	std::cout << "<--Mac header added " << std::endl;
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(), 30, "Packet wrong size after macHdr addition!");

	//macTrailer.
	packet->AddTrailer(macTrailer); //+4 bytes fixed
	std::cout << "<-- Mac trailer added " << std::endl;
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(), 34, "Packet wrong size after macTrailer addition!");

	uint32_t size = packet->GetSerializedSize();
	uint8_t buffer[size];
	packet->Serialize(buffer, size);
	Ptr<Packet> p2 = Create<Packet>(buffer, size, true);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 34, "Packet wrong size after deserialization");

	HrWpanMacHeader receivedMacHeader;
	p2->RemoveHeader(receivedMacHeader);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 24, "Packet wrong size after removing machdr");

	HrWpanMacTrailer receivedMacTrailer;
	p2->RemoveTrailer(receivedMacTrailer);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 20, "Packet wrong size after removing mactrailer");

	//Checking address
	NS_TEST_ASSERT_MSG_EQ(macTrailer, receivedMacTrailer, "The Mac Trailer is different!");

}

// ==============================================================================
class LrWpanPacketTestSuite : public TestSuite
{
public:
	LrWpanPacketTestSuite();
};

LrWpanPacketTestSuite::LrWpanPacketTestSuite()
	: TestSuite("hr-wpan-packet", UNIT)
{
	AddTestCase(new HrWpanPacketTestCase, TestCase::QUICK);
}

static LrWpanPacketTestSuite lrWpanPacketTestSuite;
