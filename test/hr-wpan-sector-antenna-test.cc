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

#include <ns3/hr-wpan-sector-antenna.h>
#include <ns3/double.h>

using namespace ns3;

////////////////// HrWpanSectorAntennaLosTestCase ////////////////

NS_LOG_COMPONENT_DEFINE("HrWpanSectorAntennaTest");

class HrWpanSectorAntennaLosTestCase : public TestCase
{
public:
	HrWpanSectorAntennaLosTestCase();
	virtual ~HrWpanSectorAntennaLosTestCase();

private:
	virtual void DoRun(void);
};

HrWpanSectorAntennaLosTestCase::HrWpanSectorAntennaLosTestCase() :
TestCase("Testing the los sector antenna gain")
{
	LogComponentEnable("HrWpanSectorAntennaTest", LOG_ALL);
}

HrWpanSectorAntennaLosTestCase::~HrWpanSectorAntennaLosTestCase()
{

}

void HrWpanSectorAntennaLosTestCase::DoRun()
{
	Ptr<HrWpan::SectorAntenna> sectorAntenna = CreateObject<HrWpan::SectorAntenna>();
	sectorAntenna->SetAttribute("Orientation", DoubleValue(DegreesToRadians(90)));
	sectorAntenna->SetAttribute("Beamwidth", DoubleValue(DegreesToRadians(20)));

	Angles firstAngle(DegreesToRadians(90), 0);
	Angles secondAngle(DegreesToRadians(99), 0);
	Angles thirdAngle(DegreesToRadians(81), 0);

	NS_TEST_ASSERT_MSG_GT(sectorAntenna->GetGainDb(firstAngle), 0, " Not working!");
	NS_TEST_ASSERT_MSG_GT(sectorAntenna->GetGainDb(secondAngle), 0, " Not working!");
	NS_TEST_ASSERT_MSG_GT(sectorAntenna->GetGainDb(thirdAngle), 0, " Not working!");

}

////////////////// HrWpanSectorAntennaNoLosTestCase ////////////////

class HrWpanSectorAntennaNoLosTestCase : public TestCase
{
public:
	HrWpanSectorAntennaNoLosTestCase();
	virtual ~HrWpanSectorAntennaNoLosTestCase();

private:
	virtual void DoRun(void);
};

HrWpanSectorAntennaNoLosTestCase::HrWpanSectorAntennaNoLosTestCase() :
TestCase("Testing the no los sector antenna gain")
{
	LogComponentEnable("HrWpanSectorAntennaTest", LOG_ALL);
}

HrWpanSectorAntennaNoLosTestCase::~HrWpanSectorAntennaNoLosTestCase()
{

}

void HrWpanSectorAntennaNoLosTestCase::DoRun()
{
	Ptr<HrWpan::SectorAntenna> sectorAntenna = CreateObject<HrWpan::SectorAntenna>();
	sectorAntenna->SetAttribute("Orientation", DoubleValue(DegreesToRadians(90)));
	sectorAntenna->SetAttribute("Beamwidth", DoubleValue(DegreesToRadians(20)));

	Angles firstAngle(DegreesToRadians(0), 0);
	Angles secondAngle(DegreesToRadians(180), 0);
	Angles thirdAngle(DegreesToRadians(270), 0);

	NS_LOG_INFO(sectorAntenna->GetGainDb(firstAngle));

	NS_TEST_ASSERT_MSG_LT(sectorAntenna->GetGainDb(firstAngle), 0, " Not working!");
	NS_TEST_ASSERT_MSG_LT(sectorAntenna->GetGainDb(secondAngle), 0, " Not working!");
}

//////////////// Test Suite //////////////////

class HrWpanSectorAntennaTestSuite : public TestSuite
{
public:
	HrWpanSectorAntennaTestSuite();
	
};

HrWpanSectorAntennaTestSuite::HrWpanSectorAntennaTestSuite()
	: TestSuite("hr-wpan-sector-antenna", UNIT)
{
	AddTestCase(new HrWpanSectorAntennaLosTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanSectorAntennaNoLosTestCase, TestCase::QUICK);
}

static HrWpanSectorAntennaTestSuite hrWpanSectorAntennaTestSuite;