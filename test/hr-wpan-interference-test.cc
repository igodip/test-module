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
#include <ns3/hr-wpan-interference-helper.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanInterferenceTest");

// This is an example TestCase.
class HrWpanInterferenceTestCase : public TestCase {
public:
	HrWpanInterferenceTestCase();
	virtual ~HrWpanInterferenceTestCase();
private:
	virtual void DoRun(void);
};

HrWpanInterferenceTestCase::HrWpanInterferenceTestCase()
	: TestCase("Test the interference sending two packets at the same time.")
{}

HrWpanInterferenceTestCase::~HrWpanInterferenceTestCase()
{

}

void
HrWpanInterferenceTestCase::DoRun(void)
{

	//Build the topology

	//Schedule packet send

	//Check that the packet has been dropped

}

// ==============================================================================
class HrWpanInterferenceTestSuite : public TestSuite
{
public:
	HrWpanInterferenceTestSuite();
};

HrWpanInterferenceTestSuite::HrWpanInterferenceTestSuite()
	: TestSuite("hr-wpan-interference", UNIT)
{
	AddTestCase(new HrWpanInterferenceTestCase, TestCase::QUICK);
}

static HrWpanInterferenceTestSuite hrWpanInterferenceTestSuite;