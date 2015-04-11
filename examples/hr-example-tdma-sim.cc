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
#include <ns3/antenna-model.h>
#include <ns3/random-variable-stream.h>

#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-devid-helper.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/hr-wpan-phy-stat-helper.h>
#include <ns3/hr-wpan-mac-stat-helper.h>
#include <ns3/hr-wpan-mac-tdma-sync.h>
#include <ns3/hr-wpan-mac-slotted-aloha-sync.h>

#include <ns3/packet-sink-helper.h>
#include <ns3/internet-module.h>
#include "ns3/applications-module.h"

#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanTdmaSim");

int main(int argc, char ** argv)
{
	LogComponentEnable("HrWpanTdmaSim", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanNetDevice", LOG_LEVEL_INFO);
	//LogComponentEnable("Node", LOG_LEVEL_WARN);
	//LogComponentEnable("HrWpanObstaclePropagationModel", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpan::SectorAntenna", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanMac", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanPhy", LOG_LEVEL_ALL);

	double lengthTop = 10;
	double obsMaxSize = 1;
	double pairDensity = 0.5;
	double obstacleDensity = 0.25;
	int rounds = 50;
	double beamwidth = 10;
	std::string reportFilename = "stats.csv";

	CommandLine cmd;
	cmd.AddValue("lengthTop", "Topology length", lengthTop);
	cmd.AddValue("obsMaxSize", "Obstacle max size", obsMaxSize);
	cmd.AddValue("pairDensity", "Number of pair sender/receiver", pairDensity);
	cmd.AddValue("obstacleDensity", "Obstacle number", obstacleDensity);
	cmd.AddValue("reportFilename", "Filename of the report", reportFilename);
	cmd.AddValue("beamwidth", "Beamwidth", beamwidth);
	cmd.AddValue("rounds", "Rounds per simulation", rounds);
	cmd.Parse(argc, argv);

	Config::SetDefault("ns3::HrWpan::SectorAntenna::Beamwidth", DoubleValue(DegreesToRadians(beamwidth)));
	//Config::SetDefault("ns3::HrWpan::SectorAntenna::Beamwidth",)

	double pairLam = pairDensity*lengthTop*lengthTop;
	double obstacleLam = obstacleDensity*lengthTop*lengthTop;

	Ptr<ErlangRandomVariable> pairPoisson = CreateObject<ErlangRandomVariable>();
	pairPoisson->SetAttribute("Lambda", DoubleValue(pairLam));

	Ptr<ErlangRandomVariable> obstaclePoisson = CreateObject<ErlangRandomVariable>();
	obstaclePoisson->SetAttribute("Lambda", DoubleValue(obstacleLam));

	std::ofstream outfile(reportFilename.c_str(), std::ios::trunc);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = &HrWpan::TopologyAggregator::getInstance();

	if (!outfile.is_open())
	{
		NS_ABORT_MSG("Can't create the file");
	}

	for (int i = 1; i <= rounds; i++)
	{
		NS_LOG_INFO("-----------------------------------");
		NS_LOG_INFO("Rounds " << i << " of " << rounds);

		int pairNumber = pairPoisson->GetInteger()+1;
		int obstacleNumber = obstaclePoisson->GetInteger();

		NS_LOG_INFO("pairNumber " << pairNumber);
		NS_LOG_INFO("obstacleNumber " << obstacleNumber);

		NodeContainer nodeContainer;
		nodeContainer.Create(pairNumber*2);

		topologyAggregator->clear();
		HrWpan::TopologyHelper topologyHelper(lengthTop, lengthTop, obsMaxSize, topologyAggregator);
		HrWpan::HrWpanHelper wpanHelper(topologyAggregator);

		NS_LOG_INFO("Installing the 802.15.3c stack");
		NetDeviceContainer netDevices = wpanHelper.Install(nodeContainer);

		NS_LOG_INFO("Placing nodes");
		topologyHelper.Install(nodeContainer);

		NS_LOG_INFO("Placing obstacles");
		topologyHelper.PlaceObstacle(obstacleNumber);

		NS_LOG_INFO("Assigning DevId to MAC");
		HrWpan::DevIdHelper::GetInstance().Install(netDevices);

		NS_LOG_INFO("Assign IP Address");
		InternetStackHelper internet;
		internet.Install(nodeContainer);

		Ipv4AddressHelper ipv4;
		ipv4.SetBase("10.0.0.0", "255.0.0.0");
		ipv4.Assign(netDevices);

		NS_LOG_INFO("Create Applications.");
		topologyHelper.InstallApplication();

		NS_LOG_INFO("Setting trace");
		HrWpan::PhyStatHelper phyStatHelper;
		phyStatHelper.attach();

		HrWpan::MacStatHelper macStatHelper;
		macStatHelper.attach();

		NS_LOG_INFO("Setting up the manager");
		Ptr<HrWpan::MacTdmaSync> tdmaSync = CreateObject<HrWpan::MacTdmaSync>();
		
		tdmaSync->AddListeners(netDevices);
		tdmaSync->Activate();
		
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

		NS_LOG_INFO("MacRx = " << macStatHelper.getRx());
		NS_LOG_INFO("MacTx = " << macStatHelper.getTx());
		NS_LOG_INFO("MacQueueDro = " << macStatHelper.getQueueDrop());
		NS_LOG_INFO("MacQueueEnq = " << macStatHelper.getQueueIn());
		NS_LOG_INFO("MacQueueDeq = " << macStatHelper.getQueueOut());
		NS_LOG_INFO("MacTotalWaitTime = " << macStatHelper.getTotalDelay());
		NS_LOG_INFO("MacAvgWaitTime = " << macStatHelper.getAvgDelay());
		NS_LOG_INFO("MacQueueReIn = " << macStatHelper.getQueueReIn());
		NS_LOG_INFO("TotalRetrasmissions = " << macStatHelper.getRtPackets());
		NS_LOG_INFO("AvgRetrasmission = " << macStatHelper.getAvgRtsPackets());

		outfile << pairNumber << ",";
		outfile << obstacleNumber << ",";

		outfile << phyStatHelper.getRxBegin() << ",";
		outfile << phyStatHelper.getRxDrop() << ",";
		outfile << phyStatHelper.getRxEnd() << ",";

		outfile << phyStatHelper.getTxBegin() << ",";
		outfile << phyStatHelper.getTxDrop() << ",";
		outfile << phyStatHelper.getTxEnd() << ",";

		outfile << macStatHelper.getRx() << ",";
		outfile << macStatHelper.getTx() << ",";
		outfile << macStatHelper.getQueueDrop() << ",";
		outfile << macStatHelper.getQueueIn() << ",";
		outfile << macStatHelper.getQueueOut() << ",";
		outfile << macStatHelper.getQueueReIn() << ",";
		outfile << macStatHelper.getAvgRtsPackets() << ",";
		outfile << macStatHelper.getAvgDelay() << std::endl;
		
		outfile.flush();
	}

	outfile.close();

	return 0;
}