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
#include <ns3/abort.h>
#include <ns3/node-container.h>
#include <ns3/animation-interface.h>
#include <ns3/node-container.h>
#include <ns3/config.h>
#include <ns3/command-line.h>

#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-devid-helper.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/hr-wpan-phy-stat-helper.h>

#include <ns3/packet-sink-helper.h>
#include <ns3/internet-module.h>
#include "ns3/applications-module.h"

#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanAnimSim");

int main(int argc, char ** argv)
{
	LogComponentEnable("HrWpanAnimSim", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpan::PhyStatHelper", LOG_LEVEL_ALL);

	double lengthTop = 20;
	double obsMaxSize = 1;
	int pairNumber = 30;
	int obstacleNumber = 30;
	int rounds = 20;
	std::string reportFilename = "stats.csv";

	CommandLine cmd;
	cmd.AddValue("lengthTop", "Topology length", lengthTop);
	cmd.AddValue("obsMaxSize", "Obstacle max size", obsMaxSize);
	cmd.AddValue("pairNumber", "Number of pair sender/receiver", pairNumber);
	cmd.AddValue("obstacleNumber", "Obstacle number", obstacleNumber);
	cmd.AddValue("reportFilename","Filename of the report",reportFilename);
	cmd.Parse(argc, argv);

	int nodeNumbers = pairNumber * 2;

	NS_LOG_INFO("Installing the 802.15.3c stack");

	std::ofstream outfile(reportFilename.c_str(), std::ios::trunc);

	if (!outfile.is_open())
	{
		
	}

	for (int i = 1; i <= rounds; i++)
	{
		NS_LOG_INFO("-----------------------------------");
		NS_LOG_INFO("Rounds " << i+1 << " of " << rounds);
		NodeContainer nodeContainer;
		nodeContainer.Create(nodeNumbers);

		Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();
		HrWpan::TopologyHelper topologyHelper(lengthTop, lengthTop, obsMaxSize, topologyAggregator);
		HrWpan::HrWpanHelper wpanHelper(topologyAggregator);

		NS_LOG_INFO("Installing the 802.15.3c stack");
		NetDeviceContainer netDevices = wpanHelper.Install(nodeContainer);

		NS_LOG_INFO("Placing nodes");
		topologyHelper.Install(nodeContainer);

		NS_LOG_INFO("Placing obstacles");
		topologyHelper.PlaceObstacle(obstacleNumber);

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
		topologyHelper.InstallApplication();

		NS_LOG_INFO("Setting trace");
		HrWpan::PhyStatHelper phyStatHelper;
		phyStatHelper.attach();

		NS_LOG_INFO("Running simulation.");
		Simulator::Run();
		Simulator::Destroy();
		NS_LOG_INFO("Done.");

		NS_LOG_INFO("Writing Stats");

		NS_LOG_INFO("RxBegin = " << phyStatHelper.getRxBegin());
		NS_LOG_INFO("RxDrop = " << phyStatHelper.getRxDrop());
		NS_LOG_INFO("RxEnd = " << phyStatHelper.getRxEnd());

		NS_LOG_INFO("TxBegin = " << phyStatHelper.getTxBegin());
		NS_LOG_INFO("TxDrop = " << phyStatHelper.getTxDrop());
		NS_LOG_INFO("TxEnd = " << phyStatHelper.getTxEnd());

		outfile << phyStatHelper.getRxBegin() << ",";
		outfile << phyStatHelper.getRxDrop() << ",";
		outfile << phyStatHelper.getRxEnd() << ",";

		outfile << phyStatHelper.getTxBegin() << ",";
		outfile << phyStatHelper.getTxDrop() << ",";
		outfile << phyStatHelper.getTxEnd() << ",";
	}
	
	outfile.close();

	return 0;
}