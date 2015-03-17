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

using namespace ns3;

////////////////// HrWpanSectorAntennaLosTestCase ////////////////

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

}

HrWpanSectorAntennaLosTestCase::~HrWpanSectorAntennaLosTestCase()
{

}

void HrWpanSectorAntennaLosTestCase::DoRun()
{

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

}

HrWpanSectorAntennaNoLosTestCase::~HrWpanSectorAntennaNoLosTestCase()
{

}

void HrWpanSectorAntennaNoLosTestCase::DoRun()
{

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