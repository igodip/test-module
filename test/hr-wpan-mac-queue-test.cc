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

}

HrWpanMacQueueTestCase::~HrWpanMacQueueTestCase()
{

}

void HrWpanMacQueueTestCase::DoRun(void)
{

	HrWpanMacQueue macQueue;
	//macQueue.

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

