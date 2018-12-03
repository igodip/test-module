// Hr Wpan Mis

#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <ns3/command-line.h>
#include <ns3/log.h>
#include <ns3/abort.h>
#include <ns3/config.h>
#include <ns3/double.h>
#include <ns3/data-rate.h>
#include <ns3/uinteger.h>
#include <ns3/angles.h>
#include <ns3/node-container.h>
#include <ns3/internet-stack-helper.h>
#include <ns3/ipv4-address-helper.h>

#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-devid-helper.h>
#include <ns3/hr-wpan-mac-slotted-aloha-sync.h>
#include <ns3/hr-wpan-phy-stat-helper.h>
#include <ns3/hr-wpan-mac-stat-helper.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/mobility-model.h>
#include <ns3/hr-wpan-line.h>
#include <ns3/hr-wpan-obstacle.h>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanMis");

int main(int argc, char** argv)
{

	LogComponentEnable("HrWpanMis",LOG_ALL);

	// Default values
	double lengthTop = 10;
	double obsMaxSize = 1;
	double pairDensity = 0.5;
	double obstacleDensity = 0.25;
	int rounds = 3;
	double beamwidth = 10;
	double trasProb = 0.6;
	std::string bitRate = "2Mb/s";
	uint32_t packetSize = 512;
	std::string reportFilename = "stats.csv";

	//Command line
	CommandLine cmd;
	cmd.AddValue("lengthTop", "Topology length", lengthTop);
	cmd.AddValue("obsMaxSize", "Obstacle max size", obsMaxSize);
	cmd.AddValue("pairDensity", "Number of pair sender/receiver", pairDensity);
	cmd.AddValue("obstacleDensity", "Obstacle number", obstacleDensity);
	cmd.AddValue("reportFilename", "Filename of the report", reportFilename);
	cmd.AddValue("beamwidth", "Beamwidth", beamwidth);
	cmd.AddValue("rounds", "Rounds per simulation", rounds);
	cmd.AddValue("trasProb", "Trasmission probability", trasProb);
	cmd.AddValue("bitRate", "Bit Rate", bitRate);
	cmd.AddValue("packetSize", "Packet Size", packetSize);
	cmd.Parse(argc, argv);

	Config::SetDefault("ns3::HrWpan::SectorAntenna::Beamwidth", DoubleValue(DegreesToRadians(beamwidth)));
	Config::SetDefault("ns3::OnOffApplication::DataRate", DataRateValue(DataRate(bitRate)));
	Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(packetSize));
	Config::SetDefault("ns3::HrWpanMac::TrasProb", DoubleValue(trasProb));

	std::ofstream outfile(reportFilename.c_str(), std::ios::trunc);

	if (!outfile.is_open())
	{
		NS_ABORT_MSG("Can't create the file");
	}

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = &HrWpan::TopologyAggregator::getInstance();

	int pairNumber = pairDensity*lengthTop*lengthTop;
	int obstacleNumber = obstacleDensity*lengthTop*lengthTop;

	for (int i = 1; i <= rounds; i++)
	{
		NS_LOG_INFO("-----------------------------------");
		NS_LOG_INFO("Rounds " << i << " of " << rounds);

		NS_LOG_INFO("pairNumber " << pairNumber);
		NS_LOG_INFO("obstacleNumber " << obstacleNumber);

		NodeContainer nodeContainer;
		nodeContainer.Create(pairNumber * 2);

		topologyAggregator->clear();
		topologyAggregator->SetBeamwidth(DegreesToRadians(beamwidth));
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

		Ptr<HrWpan::MacSlottedAlohaSync> tdmaSync = CreateObject<HrWpan::MacSlottedAlohaSync>();
		tdmaSync->AddListeners(topologyHelper.getSenderDevices());
		tdmaSync->Activate();

		NS_LOG_INFO("Saving topology");

		static char buf[2];
		static char buffer[20] = "topology";
		snprintf(buf, sizeof(buf), "%d", i);

		std::ofstream topology(strcat(buffer, buf), std::ios::trunc);

		NS_LOG_INFO("Saving nodes positions");

		for (int j = 0; j < pairNumber*2; ++j)
		{

			Ptr<HrWpan::HrWpanNetDevice> nd = DynamicCast<HrWpan::HrWpanNetDevice>(nodeContainer.Get(j)->GetDevice(0));
			
			Vector pos = nd->GetPhy()->GetMobility()->GetPosition();
			topology << pos.x << "," << pos.y << std::endl;
		}

		NS_LOG_INFO("Saving obstacles");



		const std::list< Ptr< HrWpan::Line > > lines = topologyAggregator->getContainer();
		std::list<Ptr<HrWpan::Line> > ::const_iterator itr = lines.begin();

		for (; itr != lines.end(); ++itr)
		{


			Ptr<HrWpan::Obstacle> obstacle = DynamicCast<HrWpan::Obstacle>(*itr);

			if (obstacle == 0)
			{
				continue;

			}

			topology << obstacle->getStart().x << "," << obstacle->getStart().y
				<< obstacle->getEnd().x << "," << obstacle->getEnd().y << std::endl;

		}
			
		topology.close();

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
		outfile << macStatHelper.getAvgDelay() << ",";

		for (int rtDis = 0; rtDis < 12; rtDis++)
		{
			outfile << macStatHelper.getRtDistrib(rtDis) << ",";
		}

		outfile << std::endl;

		outfile.flush();
	}
	outfile.close();

	return 0;
}

