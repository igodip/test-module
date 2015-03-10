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
#include <ns3/log.h>

using namespace ns3;

int main(int argc, char** argv)
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);
	LogComponentEnable("HrWpanHelper",LOG_ALL);
	LogComponentEnable("HrWpanMac", LOG_ALL);
	LogComponentEnable("HrWpanPhy", LOG_ALL);

	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::HrWpanHelper hrWpanHelper(topologyAggregator);
	NetDeviceContainer netDeviceContainer = hrWpanHelper.Install(nodeContainer);

	Ptr<NetDevice> netDevice1 = netDeviceContainer.Get(0);
	Ptr<NetDevice> netDevice2 = netDeviceContainer.Get(1);

	//netDevice1->Send()
	//netDevice2->Send()

	Simulator::Stop(Seconds(10.0));

	//Simulator::Schedule(Seconds(1.0), &SendOnePacket, sender, receiver);

	Simulator::Run();

	Simulator::Destroy();
}