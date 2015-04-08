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
* Author:
*/

#include <ns3/log.h>
#include <ns3/test.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanTagTestCase");

/********************* TEST CASE *********************/

class HrWpanTagTestCase : public TestCase
{
public:
	HrWpanTagTestCase();
	virtual ~HrWpanTagTestCase();

private:
	virtual void DoRun(void);
};
/********************** SUITE TEST ********************/

class HrWpanTopologyTestSuite : public TestSuite
{
public:
	HrWpanTopologyTestSuite();
};


HrWpanTopologyTestSuite::HrWpanTopologyTestSuite()
	: TestSuite("hr-wpan-topology-test", UNIT)
{
	AddTestCase(new HrWpanTopologyTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPlacingObstaclesTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPlacingNodesTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(1, 0, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(0, 1, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(-1, 0, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(0, -1, 0)), TestCase::QUICK);
}

static HrWpanTopologyTestSuite hrWpanTopologyTestSuite;