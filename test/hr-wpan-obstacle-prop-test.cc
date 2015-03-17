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
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/node-container.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-link.h>
#include <ns3/hr-wpan-obstacle.h>
#include <ns3/ptr.h>
#include <ns3/log.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanObstaclePropTest");

class HrWpanObstaclePropTestCase : public TestCase {
public:
	HrWpanObstaclePropTestCase();
	virtual ~HrWpanObstaclePropTestCase();
private:
	virtual void DoRun(void);
};

HrWpanObstaclePropTestCase::HrWpanObstaclePropTestCase()
	: TestCase("Testing the signal propagation through obstacles")
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);

	LogComponentEnable("HrWpanObstaclePropTest", LOG_LEVEL_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpanObstaclePropagationModel", LOG_LEVEL_ALL);

}

HrWpanObstaclePropTestCase::~HrWpanObstaclePropTestCase()
{

}

void HrWpanObstaclePropTestCase::DoRun(void)
{
	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::HrWpanHelper hrWpanHelper(topologyAggregator);

	Ptr<Node> node1 = nodeContainer.Get(0);
	Ptr<Node> node2 = nodeContainer.Get(1);

	Ptr<MobilityModel> senderMobility = CreateObject<ConstantPositionMobilityModel>();
	Ptr<MobilityModel> receiverMobility = CreateObject<ConstantPositionMobilityModel>();

	senderMobility->SetPosition(Vector(0, 0, 0));
	receiverMobility->SetPosition(Vector(2, 0, 0));

	node1->AggregateObject(senderMobility);
	node2->AggregateObject(receiverMobility);

	Ptr<HrWpan::Link> link = CreateObject<HrWpan::Link>();
	Ptr<HrWpan::Obstacle> obstacle = CreateObject<HrWpan::Obstacle>(1, 1, 1, -1);

	topologyAggregator->addLine(link);
	topologyAggregator->addLine(obstacle);

	link->SetReceiver(node2);
	link->SetSender(node1);

	NetDeviceContainer netDeviceContainer = hrWpanHelper.Install(nodeContainer);

	Ptr<NetDevice> netDevice1 = netDeviceContainer.Get(0);
	Ptr<NetDevice> netDevice2 = netDeviceContainer.Get(1);

	netDevice1->SetAddress(HrWpanDevId("01"));
	netDevice2->SetAddress(HrWpanDevId("02"));

	Ptr<Packet> p = Create<Packet>(20);

	netDevice1->Send(p, HrWpanDevId("02"), 1);
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

HrWpanNoObstaclePropTestCase::HrWpanNoObstaclePropTestCase()
	: TestCase("Testing the signal propagation through obstacles")
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);

	LogComponentEnable("HrWpanObstaclePropTest", LOG_LEVEL_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpanObstaclePropagationModel", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpanPhy", LOG_LEVEL_ALL);

}

HrWpanNoObstaclePropTestCase::~HrWpanNoObstaclePropTestCase()
{

}

void HrWpanNoObstaclePropTestCase::DoRun(void)
{
	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::HrWpanHelper hrWpanHelper(topologyAggregator);

	Ptr<Node> node1 = nodeContainer.Get(0);
	Ptr<Node> node2 = nodeContainer.Get(1);

	Ptr<MobilityModel> senderMobility = CreateObject<ConstantPositionMobilityModel>();
	Ptr<MobilityModel> receiverMobility = CreateObject<ConstantPositionMobilityModel>();

	senderMobility->SetPosition(Vector(0, 0, 0));
	receiverMobility->SetPosition(Vector(2, 0, 0));

	node1->AggregateObject(senderMobility);
	node2->AggregateObject(receiverMobility);

	Ptr<HrWpan::Link> link = CreateObject<HrWpan::Link>();
	Ptr<HrWpan::Obstacle> obstacle = CreateObject<HrWpan::Obstacle>(1, 1, 1, 3);

	topologyAggregator->addLine(link);
	topologyAggregator->addLine(obstacle);

	link->SetReceiver(node2);
	link->SetSender(node1);

	NetDeviceContainer netDeviceContainer = hrWpanHelper.Install(nodeContainer);

	Ptr<NetDevice> netDevice1 = netDeviceContainer.Get(0);
	Ptr<NetDevice> netDevice2 = netDeviceContainer.Get(1);

	netDevice1->SetAddress(HrWpanDevId("01"));
	netDevice2->SetAddress(HrWpanDevId("02"));

	Ptr<Packet> p = Create<Packet>(20);

	netDevice1->Send(p, HrWpanDevId("02"), 1);
}


// ==============================================================================
class HrWpanObstaclePropTestSuite : public TestSuite
{
public:
	HrWpanObstaclePropTestSuite();
};

HrWpanObstaclePropTestSuite::HrWpanObstaclePropTestSuite()
	: TestSuite("hr-wpan-obstacle-prop-test", UNIT)
{
	AddTestCase(new HrWpanObstaclePropTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanNoObstaclePropTestCase, TestCase::QUICK);
}

static HrWpanObstaclePropTestSuite hrWpanObstaclePropTestSuite;
