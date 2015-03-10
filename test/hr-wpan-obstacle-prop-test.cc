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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include <ns3/test.h>
#include <ns3/packet.h>
#include <ns3/hr-wpan-phy.h>
#include <ns3/mobility-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/hr-wpan-phy-ula-antenna.h>
#include <ns3/log.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("hr-wpan-packet-test");

// This is an example TestCase.
class HrWpanObstaclePropTestCase : public TestCase {
public:
	HrWpanObstaclePropTestCase();
	virtual ~HrWpanObstaclePropTestCase();
private:
	virtual void DoRun(void);
};

HrWpanObstaclePropTestCase::HrWpanObstaclePropTestCase()
	: TestCase("Testing the signal propagation through obstacles")
{}

HrWpanObstaclePropTestCase::~HrWpanObstaclePropTestCase()
{

}

void
HrWpanObstaclePropTestCase::DoRun(void)
{

}

/**
 * \class	HrWpanNoObstaclePropTestCase
 *
 * \brief	A hr wpan no obstacle propagation test case.
 *
 * \author	Igor
 * \date	10/03/2015
 */

class HrWpanNoObstaclePropTestCase : public TestCase {

public:
	HrWpanNoObstaclePropTestCase();
	virtual ~HrWpanNoObstaclePropTestCase();
private:
	virtual void DoRun(void);

};



// ==============================================================================
class HrWpanObstaclePropTestSuite : public TestSuite
{
public:
	HrWpanObstaclePropTestSuite();
};

HrWpanObstaclePropTestSuite::HrWpanObstaclePropTestSuite()
	: TestSuite("hr-wpan-obstacle-prop", UNIT)
{
	AddTestCase(new HrWpanObstaclePropTestCase, TestCase::QUICK);
}

static HrWpanObstaclePropTestSuite hrWpanObstaclePropTestSuite;
