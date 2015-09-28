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
#include <ns3/hr-wpan-ctrl-packet-factory.h>
#include <ns3/nstime.h>
#include <ns3/hr-wpan-dev-id.h>
#include <ns3/packet.h>
#include <ns3/log.h>
#include <ns3/node-container.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/command-line.h>
#include <ns3/hr-wpan-devid-helper.h>
#include <ns3/hr-wpan-phy-stat-helper.h>
#include <ns3/hr-wpan-mac-stat-helper.h>
#include <ns3/ipv4-address-helper.h>
#include <ns3/internet-stack-helper.h>
#include <ns3/config.h>
#include <ns3/double.h>
#include <ns3/uinteger.h>
#include <ns3/data-rate.h>
#include <ns3/angles.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrExampleCsma");

int main(int argc, char** argv)
{

	LogComponentEnable("HrExampleCsma", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpanMac", LOG_LEVEL_INFO);
	//LogComponentEnable("HrWpanNetDevice", LOG_LEVEL_INFO);
	LogComponentEnable("HrWpanPhy", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanMacSapAsync", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanPhyRxOnState", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanPhyTxOnState", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanPhyRxBusyState", LOG_LEVEL_ALL);
	//LogComponentEnable("HrWpanCtrlPacketFactory", LOG_LEVEL_ALL);

	double lengthTop = 10;
	double obsMaxSize = 1;
	double pairDensity = 0.5;
	double obstacleDensity = 0.25;
	int rounds = 50;
	double beamwidth = 180;
	std::string bitRate = "100kb/s";
	uint32_t packetSize = 512;
	std::string reportFilename = "stats.csv";

	CommandLine cmd;
	cmd.AddValue("lengthTop", "Topology length", lengthTop);
	cmd.AddValue("obsMaxSize", "Obstacle max size", obsMaxSize);
	cmd.AddValue("pairDensity", "Number of pair sender/receiver", pairDensity);
	cmd.AddValue("obstacleDensity", "Obstacle number", obstacleDensity);
	cmd.AddValue("reportFilename", "Filename of the report", reportFilename);
	cmd.AddValue("beamwidth", "Beamwidth", beamwidth);
	cmd.AddValue("rounds", "Rounds per simulation", rounds);
	cmd.AddValue("bitRate", "Bit Rate", bitRate);
	cmd.AddValue("packetSize", "Packet Size", packetSize);
	cmd.Parse(argc, argv);

	Config::SetDefault("ns3::HrWpan::SectorAntenna::Beamwidth", DoubleValue(DegreesToRadians(beamwidth)));
	Config::SetDefault("ns3::OnOffApplication::DataRate", DataRateValue(DataRate(bitRate)));
	Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(packetSize));

	NS_LOG_INFO("Creating factory");
	HrWpanCtrlPacketFactory & factory = HrWpanCtrlPacketFactory::getInstance();
	
	HrWpan::DevId sender("01:01");
	HrWpan::DevId receiver("01:02");
	Time t = Seconds(1.0);

	NS_LOG_INFO("Rts Packet");

	Ptr<Packet> p = factory.CreateRtsPacket(sender, receiver, t);
	
	HrWpan::DevId sender2,receiver2;
	Time t2;

	factory.ParseRtsPacket(p, sender2, receiver2, t2);

	NS_LOG_INFO(receiver2);
	NS_LOG_INFO(sender2);
	NS_LOG_INFO("Time " << t2);

	NS_LOG_INFO("Cts Packet");

	Ptr<Packet> p1 = factory.CreateCtsPacket(receiver, t);

	factory.ParseCtsPacket(p1,receiver2, t2);

	NS_LOG_INFO(receiver2);
	NS_LOG_INFO("Time " << t2);

	NS_LOG_INFO("Topology aggregator");
	Ptr<HrWpan::TopologyAggregator> topologyAggregator = &HrWpan::TopologyAggregator::getInstance();

	NS_LOG_INFO("Creating two nodes");

	NodeContainer nodeContainer;
	nodeContainer.Create(4);

	HrWpan::TopologyHelper topologyHelper(lengthTop, lengthTop, obsMaxSize, topologyAggregator);

	NS_LOG_INFO("Installing HrWpan Stack");
	HrWpan::HrWpanHelper hrWpanHelper(topologyAggregator);
	NetDeviceContainer netDevices = hrWpanHelper.Install(nodeContainer);

	NS_LOG_INFO("Placing nodes");
	topologyHelper.Install(nodeContainer);

	NS_LOG_INFO("Placing obstacles");
	//topologyHelper.PlaceObstacle(20);

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
	/*
	NS_LOG_INFO("Setting up the manager");
	Ptr<HrWpan::MacTdmaSync> tdmaSync = CreateObject<HrWpan::MacTdmaSync>();

	tdmaSync->AddListeners(topologyHelper.getSenderDevices());
	tdmaSync->Activate();
	*/

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

	return 0;
}