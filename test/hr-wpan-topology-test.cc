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
#include <ns3/hr-wpan-sector-antenna.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-link.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/hr-wpan-dev-id.h>

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
	//LogComponentEnableAll(LOG_PREFIX_FUNC);
	//LogComponentEnable("HrWpan::TopologyHelper", LOG_ALL);
	//LogComponentEnable("HrWpan::Link", LOG_ALL);
	//LogComponentEnable("HrWpanTopologyTestCase", LOG_ALL);

}

HrWpanTopologyTestCase::~HrWpanTopologyTestCase()
{

}

void HrWpanTopologyTestCase::DoRun(void)
{

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	NodeContainer nodes;
	nodes.Create(20);

	HrWpan::TopologyHelper topologyHelper(10, 10, 3, topologyAggregator);
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
	//LogComponentEnableAll(LOG_PREFIX_FUNC);
	//LogComponentEnable("HrWpan::TopologyHelper", LOG_ALL);
	//LogComponentEnable("HrWpan::TopologyAggregator", LOG_ALL);
	//LogComponentEnable("HrWpanTopologyTestCase", LOG_ALL);
	//LogComponentEnable("ObjectBase", LOG_ALL);
	//LogComponentEnable("Object", LOG_ALL);
}

HrWpanPlacingObstaclesTestCase::~HrWpanPlacingObstaclesTestCase()
{

}


void HrWpanPlacingObstaclesTestCase::DoRun()
{

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::TopologyHelper topologyHelper(10, 10, 3, topologyAggregator);
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

	HrWpan::TopologyHelper topologyHelper(10, 10, 3, topologyAggregator);
	topologyHelper.Install(nodes);

}

/********************* TEST CASE *********************/

class HrWpanSteeringAntennaTestCase : public TestCase
{
public:
	HrWpanSteeringAntennaTestCase(Vector senderPos, Vector receiverPos);
	virtual ~HrWpanSteeringAntennaTestCase();

private:
	virtual void DoRun(void);

	NodeContainer nodeContainer;

	Ptr<HrWpan::TopologyAggregator> topologyAggregator;
	Ptr<HrWpan::Link> link;
};

HrWpanSteeringAntennaTestCase::HrWpanSteeringAntennaTestCase(Vector senderVec, Vector receiverVec)
	: TestCase("Steering antenna test case"), nodeContainer()
{
	//LogComponentEnable("HrWpanTopologyTestCase", LOG_ALL);
	//LogComponentEnable("HrWpan::TopologyHelper", LOG_ALL);
	//LogComponentEnable("SingleModelSpectrumChannel", LOG_ALL);
	LogComponentEnable("HrWpan::SectorAntenna", LOG_ALL);

	topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	nodeContainer.Create(2);

	Ptr<Node> sender = nodeContainer.Get(0);
	Ptr<Node> receiver = nodeContainer.Get(1);

	Ptr<ConstantPositionMobilityModel> senderPos =
		CreateObject<ConstantPositionMobilityModel>();

	senderPos->SetPosition(senderVec);

	sender->AggregateObject(senderPos);

	Ptr<ConstantPositionMobilityModel> receiverPos =
		CreateObject<ConstantPositionMobilityModel>();

	receiverPos->SetPosition(receiverVec);

	receiver->AggregateObject(receiverPos);

	link = CreateObject<HrWpan::Link>();

	link->SetSender(nodeContainer.Get(0));
	link->SetReceiver(nodeContainer.Get(1));



}

HrWpanSteeringAntennaTestCase::~HrWpanSteeringAntennaTestCase()
{
	link->Dispose();
}


void HrWpanSteeringAntennaTestCase::DoRun()
{

	HrWpan::HrWpanHelper wpanHelper(topologyAggregator);
	NetDeviceContainer netDevCont = wpanHelper.Install(nodeContainer);

	HrWpan::TopologyHelper::steerAntennas(link);

	netDevCont.Get(0)->Send(Create<Packet>(20), HrWpanDevId("FF"), 1);


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
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(1, 0, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(0, 1, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(-1, 0, 0)), TestCase::QUICK);
	AddTestCase(new HrWpanSteeringAntennaTestCase(Vector(0, 0, 0), Vector(0, -1, 0)), TestCase::QUICK);
}

static HrWpanTopologyTestSuite hrWpanTopologyTestSuite;

