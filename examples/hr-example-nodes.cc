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
* Author:
*	Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include <ns3/hr-wpan-helper.h>
#include <ns3/simulator.h>
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/mac48-address.h>
#include <ns3/hr-wpan-devid-helper.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/log.h>

using namespace ns3;


int main(int argc, char** argv)
{
	LogComponentEnable("HrWpanMacSapAsync", LOG_ALL);

	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::HrWpanHelper hrWpanHelper(topologyAggregator);

	Ptr<Node> node1 = nodeContainer.Get(0);
	Ptr<Node> node2 = nodeContainer.Get(1);

	Ptr<MobilityModel> senderMobility = CreateObject<ConstantPositionMobilityModel>();
	Ptr<MobilityModel> receiverMobility = CreateObject<ConstantPositionMobilityModel>();

	node1->AggregateObject(senderMobility);
	node2->AggregateObject(receiverMobility);

	NetDeviceContainer netDeviceContainer = hrWpanHelper.Install(nodeContainer);

	Ptr<NetDevice> netDevice1 = netDeviceContainer.Get(0);
	Ptr<NetDevice> netDevice2 = netDeviceContainer.Get(1);

	netDevice1->SetAddress(Mac48Address::Allocate());
	netDevice2->SetAddress(Mac48Address::Allocate());

	HrWpan::DevIdHelper::GetInstance().Install(netDeviceContainer);

	Simulator::Stop(Seconds(10.0));
	//Simulator::ScheduleWithContext(1,Seconds(2.0), &SendOnePacket, netDevice1);
	Simulator::Run();

	Simulator::Destroy();
}