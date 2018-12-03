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
	
	const char * addr = "11:12";

	HrWpan::MacHeader macHdr(HrWpan::HRWPAN_FRAME_BEACON, 0);
	macHdr.SetSecDisable();
	
	HrWpan::DevId dstAddress(addr);
	macHdr.setDstAddress(dstAddress);

	HrWpan::DevId srcAddress(addr);
	macHdr.setSrcAddress(srcAddress);

	HrWpan::MacTrailer macTrailer;
	
	Ptr<Packet> packet = Create<Packet>(20); // dummy data
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(),20, "Packed created with unexpected size!");

	packet->AddHeader(macHdr); //+10 bytes fixed
	std::cout << "<--Mac header added " << std::endl;
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(), 32, "Packet wrong size after macHdr addition!");

	//macTrailer.
	packet->AddTrailer(macTrailer); //+4 bytes fixed
	std::cout << "<-- Mac trailer added " << std::endl;
	NS_TEST_ASSERT_MSG_EQ(packet->GetSize(), 36, "Packet wrong size after macTrailer addition!");

	uint32_t size = packet->GetSerializedSize();
	uint8_t buffer[size];
	packet->Serialize(buffer, size);
	Ptr<Packet> p2 = Create<Packet>(buffer, size, true);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 36, "Packet wrong size after deserialization");

	HrWpan::MacHeader receivedMacHeader;
	p2->RemoveHeader(receivedMacHeader);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 24, "Packet wrong size after removing machdr");

	HrWpan::MacTrailer receivedMacTrailer;
	p2->RemoveTrailer(receivedMacTrailer);

	NS_TEST_ASSERT_MSG_EQ(p2->GetSize(), 20, "Packet wrong size after removing mactrailer");

	//Checking header
	

	//Checking address
	HrWpan::DevId srcReceivedAddress = receivedMacHeader.getSrcAddress();
	NS_TEST_ASSERT_MSG_EQ(srcReceivedAddress, srcAddress, "The srcAddress is different!");

	HrWpan::DevId dstReceivedAddress = receivedMacHeader.getDstAddress();
	std::cout << dstReceivedAddress << std::endl;
	NS_TEST_ASSERT_MSG_EQ(dstReceivedAddress, dstAddress, "The dstAddress is different!");

	//Checking Trailer
	NS_TEST_ASSERT_MSG_EQ(macTrailer, receivedMacTrailer, "The Mac Trailer is different!");

}

// ==============================================================================

class HrWpanPacketTypeTestCase : public TestCase {
public:
	HrWpanPacketTypeTestCase();
	virtual ~HrWpanPacketTypeTestCase();
private:
	virtual void DoRun(void);
};

HrWpanPacketTypeTestCase::HrWpanPacketTypeTestCase()
	: TestCase("Test the 802.15.3c MAC header and trailer classes")
{}

HrWpanPacketTypeTestCase::~HrWpanPacketTypeTestCase()
{

}

void HrWpanPacketTypeTestCase::DoRun(void)
{

}

// ==============================================================================

class HrWpanPacketHeaderTestCase : public TestCase {
public:
	HrWpanPacketHeaderTestCase();
	virtual ~HrWpanPacketHeaderTestCase();
private:
	virtual void DoRun(void);
};

HrWpanPacketHeaderTestCase::HrWpanPacketHeaderTestCase()
	: TestCase("Test the 802.15.3c MAC header classes")
{}

HrWpanPacketHeaderTestCase::~HrWpanPacketHeaderTestCase()
{

}

void HrWpanPacketHeaderTestCase::DoRun(void)
{

}

// ==============================================================================

class HrWpanPacketTrailerTestCase : public TestCase {
public:
	HrWpanPacketTrailerTestCase();
	virtual ~HrWpanPacketTrailerTestCase();
private:
	virtual void DoRun(void);
};

HrWpanPacketTrailerTestCase::HrWpanPacketTrailerTestCase()
	: TestCase("Test the 802.15.3c MAC trailer class")
{}

HrWpanPacketTrailerTestCase::~HrWpanPacketTrailerTestCase()
{

}

void HrWpanPacketTrailerTestCase::DoRun(void)
{

	Ptr<Packet> packet = Create<Packet>(30);
	HrWpan::MacTrailer trailer;

	


}

// ==============================================================================

class HrWpanPacketTestSuite : public TestSuite
{
public:
	HrWpanPacketTestSuite();
};

HrWpanPacketTestSuite::HrWpanPacketTestSuite()
	: TestSuite("hr-wpan-packet", UNIT)
{
	AddTestCase(new HrWpanPacketTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPacketTypeTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPacketHeaderTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPacketTrailerTestCase, TestCase::QUICK);
}

static HrWpanPacketTestSuite hrWpanPacketTestSuite;
