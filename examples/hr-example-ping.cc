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


#include <ns3/log.h>
#include <ns3/node-container.h>
#include <ns3/animation-interface.h>
#include <ns3/node-container.h>
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-devid-helper.h>

#include <ns3/on-off-helper.h>
#include <ns3/internet-module.h>
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanExamplePing");

int main(int argc, char ** argv)
{

	
	//LogComponentEnable("HrWpanExamplePing", LOG_ALL);
	//LogComponentEnable("HrWpanMacSapAsync", LOG_ALL);
	//LogComponentEnable("HrWpanPhy", LOG_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpan::SectorAntenna", LOG_LEVEL_ALL);

	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();
	HrWpan::TopologyHelper topologyHelper(20, 20,3,topologyAggregator);
	HrWpan::HrWpanHelper wpanHelper(topologyAggregator);

	NS_LOG_INFO("Installing the 802.15.3c stack");
	NetDeviceContainer netDevices = wpanHelper.Install(nodeContainer);

	NS_LOG_INFO("Placing nodes");
	topologyHelper.Install(nodeContainer);

	NS_LOG_INFO("Placing obstacles");
	topologyHelper.PlaceObstacle(2);

	NS_LOG_INFO("Assigning DevId to MAC");
	HrWpan::DevIdHelper devIdHelper;
	devIdHelper.Install(netDevices);


	NS_LOG_INFO("Assign IP Address");
	InternetStackHelper internet;
	internet.Install(nodeContainer);
	
	Ipv4AddressHelper ipv4;
	ipv4.SetBase("192.168.1.0", "255.255.255.0");
	ipv4.Assign(netDevices);
	
	NS_LOG_INFO("Create Applications.");
	OnOffHelper onoff("ns3::UdpSocketFactory",
		Address(InetSocketAddress(Ipv4Address("255.255.255.255"), 15)));
	onoff.SetConstantRate(DataRate("500kb/s"));

	ApplicationContainer app = onoff.Install(nodeContainer.Get(0));
	// Start the application
	app.Start(Seconds(1.0));
	app.Stop(Seconds(10.0));

	PacketSinkHelper sink("ns3::UdpSocketFactory",
		Address(InetSocketAddress(Ipv4Address::GetAny(), 15)));

	app = sink.Install(nodeContainer);
	app.Start(Seconds (1.0));
	app.Stop(Seconds (10.0));

	NS_LOG_INFO("Setting trace");
	AsciiTraceHelper ascii;
	wpanHelper.EnableAsciiAll(ascii.CreateFileStream("hrwpan-ping.tr"));
	wpanHelper.EnablePcapAll("hrwpan-ping", false);

	AnimationInterface animInterface("sim.xml");
	//animInterface.

	NS_LOG_INFO("Running simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}