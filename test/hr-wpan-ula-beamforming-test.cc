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
#include <ns3/hr-wpan-phy-ula-antenna.h>
#include <ns3/hr-wpan-phy-ula-beamforming.h>
#include <cmath>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanUlaBeamformingTestCase");

class HrWpanUlaBeamformingTestCase : public TestCase
{
public:
	HrWpanUlaBeamformingTestCase();
	virtual ~HrWpanUlaBeamformingTestCase();

private:
	virtual void DoRun(void);

	uint32_t m_received;
};

HrWpanUlaBeamformingTestCase::HrWpanUlaBeamformingTestCase()
	: TestCase("Test the Beamforming procedure")
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);
	LogComponentEnable("HrWpanUlaBeamformingTestCase", LOG_LEVEL_ALL);

}

HrWpanUlaBeamformingTestCase::~HrWpanUlaBeamformingTestCase()
{
	
}

void HrWpanUlaBeamformingTestCase::DoRun(void)
{
	HrWpanPhyUlaParams params1 = HrWpanPhyUlaBeamforming::GetInstance().GetParamsByOdpNumber(1);
	HrWpanPhyUlaParams params2 = HrWpanPhyUlaBeamforming::GetInstance().GetParamsByOdpNumber(2);

	Ptr<HrWpanPhyUlaAntenna> antenna1 = CreateObject<HrWpanPhyUlaAntenna>();
	Ptr<HrWpanPhyUlaAntenna> antenna2 = CreateObject<HrWpanPhyUlaAntenna>();

	antenna1->SetUlaParams(params1);
	antenna2->SetUlaParams(params2);

	NS_LOG_UNCOND(antenna1->GetGainDb(Angles(180, 0)));

}

class HrWpanUlaBeamformingTestSuite : public TestSuite
{
public:
	HrWpanUlaBeamformingTestSuite();
};

HrWpanUlaBeamformingTestSuite::HrWpanUlaBeamformingTestSuite()
	: TestSuite("hr-wpan-ula-beamforming", UNIT)
{
	AddTestCase(new HrWpanUlaBeamformingTestCase, TestCase::QUICK);
}

static HrWpanUlaBeamformingTestSuite hrWpanUlaBeamformingTestSuite;

