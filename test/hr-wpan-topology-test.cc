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
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/double.h>
#include <ns3/node-container.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanTopologyTestCase");

/********************* TEST CASE *********************/

class HrWpanTopologyTestCase : public TestCase
{
public:
	HrWpanTopologyTestCase();
	virtual ~HrWpanTopologyTestCase();

private:
	virtual void DoRun(void);
};

HrWpanTopologyTestCase::HrWpanTopologyTestCase()
	: TestCase("Test the topology creation")
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);
	LogComponentEnable("HrWpan::TopologyHelper", LOG_ALL);
	LogComponentEnable("HrWpan::Link", LOG_ALL);
	LogComponentEnable("HrWpanTopologyTestCase", LOG_ALL);

}

HrWpanTopologyTestCase::~HrWpanTopologyTestCase()
{

}

void HrWpanTopologyTestCase::DoRun(void)
{

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	NodeContainer nodes;
	nodes.Create(20);

	HrWpan::TopologyHelper topologyHelper(10, 10,topologyAggregator);
	topologyHelper.Install(nodes);
	topologyHelper.PlaceObstacle(20);

}

/********************* TEST CASE *********************/

class HrWpanPlacingObstaclesTestCase : public TestCase
{
public:
	HrWpanPlacingObstaclesTestCase();
	virtual ~HrWpanPlacingObstaclesTestCase();

private:
	virtual void DoRun(void);
};

HrWpanPlacingObstaclesTestCase::HrWpanPlacingObstaclesTestCase() 
	: TestCase("Placing obstacle test")
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);
	LogComponentEnable("HrWpan::TopologyHelper", LOG_ALL);
	//LogComponentEnable("HrWpan::TopologyAggregator", LOG_ALL);
	LogComponentEnable("HrWpanTopologyTestCase", LOG_ALL);
	//LogComponentEnable("ObjectBase", LOG_ALL);
	//LogComponentEnable("Object", LOG_ALL);
}

HrWpanPlacingObstaclesTestCase::~HrWpanPlacingObstaclesTestCase()
{
	
}


void HrWpanPlacingObstaclesTestCase::DoRun()
{

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::TopologyHelper topologyHelper(10, 10,topologyAggregator);
	topologyHelper.PlaceObstacle(20);

}

/********************* TEST CASE *********************/

class HrWpanPlacingNodesTestCase : public TestCase
{
public:
	HrWpanPlacingNodesTestCase();
	virtual ~HrWpanPlacingNodesTestCase();

private:
	virtual void DoRun(void);
};

HrWpanPlacingNodesTestCase::HrWpanPlacingNodesTestCase()
	: TestCase("Placing nodes Test")
{

}

HrWpanPlacingNodesTestCase::~HrWpanPlacingNodesTestCase()
{

}


void HrWpanPlacingNodesTestCase::DoRun()
{
	
	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	NodeContainer nodes;
	nodes.Create(20);

	HrWpan::TopologyHelper topologyHelper(10, 10, topologyAggregator);
	topologyHelper.Install(nodes);
	
}

/********************* TEST SUITE *********************/

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
}

static HrWpanTopologyTestSuite hrWpanTopologyTestSuite;
