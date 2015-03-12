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
#include <ns3/log.h>
#include <ns3/hr-wpan-helper.h>
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanNetDeviceTest");

// This is an example TestCase.
class HrWpanNetDeviceTestCase : public TestCase {
public:
	HrWpanNetDeviceTestCase();
	virtual ~HrWpanNetDeviceTestCase();
private:
	virtual void DoRun(void);
};

HrWpanNetDeviceTestCase::HrWpanNetDeviceTestCase()
	: TestCase("Sending one packet from one device to another one")
{
	
}

HrWpanNetDeviceTestCase::~HrWpanNetDeviceTestCase()
{

}

void HrWpanNetDeviceTestCase::DoRun(void)
{
	Ptr<HrWpan::TopologyAggregator > aggregator = CreateObject<HrWpan::TopologyAggregator>();
	HrWpan::HrWpanHelper helper(aggregator);

	NodeContainer nodeContainer;
	nodeContainer.Create(2);
	
}

// ==============================================================================
class HrWpanNetDeviceTestSuite : public TestSuite
{
public:
	HrWpanNetDeviceTestSuite();
};

HrWpanNetDeviceTestSuite::HrWpanNetDeviceTestSuite()
	: TestSuite("hr-wpan-net-device-test-suite", UNIT)
{
	AddTestCase(new HrWpanNetDeviceTestSuite, TestCase::QUICK);
}

static HrWpanNetDeviceTestSuite hrWpanNetDeviceTestSuite;
