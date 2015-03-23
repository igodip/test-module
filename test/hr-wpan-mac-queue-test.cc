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
* Author: Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include <ns3/test.h>
#include <ns3/log.h>
#include <ns3/hr-wpan-mac-queue.h>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanMacQueueTestCase");

class HrWpanMacQueueTestCase : public TestCase
{
public:
	HrWpanMacQueueTestCase();
	virtual ~HrWpanMacQueueTestCase();

private:
	virtual void DoRun(void);

	uint32_t m_received;
};

HrWpanMacQueueTestCase::HrWpanMacQueueTestCase()
	: TestCase("Test the MAC Queue")
{
	LogComponentEnable("HrWpanMacQueueTestCase",LOG_ALL);
}

HrWpanMacQueueTestCase::~HrWpanMacQueueTestCase()
{

}

void HrWpanMacQueueTestCase::DoRun(void)
{

	HrWpan::MacQueue macQueue;
	Ptr<Packet> p1 = Create<Packet>(30);
	Ptr<Packet> p2 = Create<Packet>(40);
	Ptr<Packet> p3 = Create<Packet>(50);

	macQueue.Enqueue(p1);
	NS_TEST_ASSERT_MSG_EQ(macQueue.GetNPackets(), 1, "Queue size not matching!");
	macQueue.Enqueue(p2);
	NS_TEST_ASSERT_MSG_EQ(macQueue.GetNPackets(), 2, "Queue size not matching!");
	macQueue.Enqueue(p3);
	NS_TEST_ASSERT_MSG_EQ(macQueue.GetNPackets(), 3, "Queue size not matching!");

	Ptr<Packet> p4  = macQueue.Dequeue();

	NS_TEST_ASSERT_MSG_EQ(p1, p4, "FIFO not working properly!");
	NS_TEST_ASSERT_MSG_EQ(macQueue.GetNPackets(), 2, "Queue size not matching!");
	Ptr<Packet> p5 = macQueue.Dequeue();

	NS_TEST_ASSERT_MSG_EQ(p2, p5, "FIFO not working properly!");
	NS_TEST_ASSERT_MSG_EQ(macQueue.GetNPackets(), 1, "Queue size not matching!");
	
	Ptr<Packet> p6 = macQueue.Dequeue();
	NS_TEST_ASSERT_MSG_EQ(p3, p6, "FIFO not working properly!");

	Ptr<Packet> p7 = macQueue.Dequeue();
	NS_TEST_ASSERT_MSG_EQ(p7, 0, "FIFO not working properly!");

}

class HrWpanMacQueueTestSuite : public TestSuite
{
public:
	HrWpanMacQueueTestSuite();
};

HrWpanMacQueueTestSuite::HrWpanMacQueueTestSuite()
	: TestSuite("hr-wpan-mac-queue", UNIT)
{
	AddTestCase(new HrWpanMacQueueTestCase, TestCase::QUICK);
}

static HrWpanMacQueueTestSuite hrWpanMacQueueTestSuite;

