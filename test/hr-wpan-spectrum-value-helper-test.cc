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

#include <ns3/log.h>
#include <ns3/test.h>
#include <ns3/hr-wpan-spectrum-value-helper.h>
#include <ns3/spectrum-value.h>

#include <cmath>

using namespace ns3;

class HrWpanSpectrumValueHelperTestCase : public TestCase
{
public:
	HrWpanSpectrumValueHelperTestCase();
	virtual ~HrWpanSpectrumValueHelperTestCase();

private:
	virtual void DoRun(void);
};

HrWpanSpectrumValueHelperTestCase::HrWpanSpectrumValueHelperTestCase()
	: TestCase("Test the 802.15.3c SpectrumValue helper class")
{

}

void HrWpanSpectrumValueHelperTestCase::DoRun()
{
	HrWpanSpectrumValueHelper helper;
}

// ======================================================================
// 

class HrWpanSpectrumValueHelperTestSuite : public TestSuite
{
public:
	HrWpanSpectrumValueHelperTestSuite();
};

HrWpanSpectrumValueHelperTestSuite::HrWpanSpectrumValueHelperTestSuite()
	: TestSuite("hr-wpan-spectrum-value-helper", UNIT)
{
	AddTestCase(new HrWpanSpectrumValueHelperTestCase, TestCase::QUICK);
}

static HrWpanSpectrumValueHelperTestSuite lrWpanSpectrumValueHelperTestSuite;
