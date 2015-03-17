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
#include <ns3/test.h>
#include <ns3/command-line.h>
#include <ns3/node-container.h>
#include <ns3/simulator.h>
#include <ns3/hr-wpan-topology-helper.h>
#include <ns3/hr-wpan-helper.h>
#include <ns3/hr-wpan-topology-aggregator.h>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrExampleSimulation");

int main(int argc, char ** argv)
{

	bool verbose = true;
	uint32_t nPairs = 10;
	double areaLength = 20;

	CommandLine cmd;
	cmd.AddValue("pairs", "Number of pairs", nPairs);
	cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
	cmd.AddValue("areaLength", "Size of areaLength", areaLength);
	
	cmd.Parse(argc, argv);

	uint32_t nNodes = 2 * nPairs;
	
	NodeContainer nodeContainer;
	nodeContainer.Create(nNodes);

	Ptr<HrWpan::TopologyAggregator> toplogyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::TopologyHelper topologyHelper(areaLength, areaLength,3,toplogyAggregator);
	topologyHelper.Install(nodeContainer);

	HrWpan::HrWpanHelper hrWpanHelper(toplogyAggregator);
	hrWpanHelper.Install(nodeContainer);

	Simulator::Stop(Seconds(10.0));

	Simulator::Run();

	Simulator::Destroy();
}