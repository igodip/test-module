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
#include <ns3/log.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("hr-wpan-phy-state-test");

class HrWpanPhyStateTestCase : public TestCase {
public:
	HrWpanPhyStateTestCase();
	virtual ~HrWpanPhyStateTestCase();
private:
	virtual void DoRun(void);
};

HrWpanPhyStateTestCase::HrWpanPacketTestCase()
	: TestCase("Test the 802.15.3c MAC header and trailer classes")
{}

HrWpanPhyStateTestCase::~HrWpanPacketTestCase()
{
}


class HrWpanPhyStateTestSuite : public TestSuite
{
public:
	HrWpanPhyStateTestSuite();
};

HrWpanPhyStateTestSuite::HrWpanPacketTestSuite()
	: TestSuite("hr-wpan-phy-state-packet", UNIT)
{
	AddTestCase(new HrWpanPhyStateTestCase, TestCase::QUICK);
}

static HrWpanPhyStateTestSuite hrWpanPacketTestSuite;