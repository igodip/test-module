// Hr Wpan Mis

#include <string>

#include <ns3/command-line.h>

int main(int argc, char** argv)
{

	// Default values
	double lengthTop = 10;
	double obsMaxSize = 1;
	double pairDensity = 0.5;
	double obstacleDensity = 0.25;
	int rounds = 50;
	double beamwidth = 10;
	double trasProb = 0.6;
	std::string bitRate = "6Mb/s";
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



	return 0;
}

