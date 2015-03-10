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

using namespace ns3;

int main(int argc, char ** argv)
{

	NodeContainer nodeContainer;
	nodeContainer.Create(30);

	Ptr<HrWpan::TopologyAggregator> topologyAggregator = CreateObject<HrWpan::TopologyAggregator>();

	HrWpan::TopologyHelper topologyHelper(20,20,topologyAggregator);
	
	HrWpan::HrWpanHelper wpanHelper(topologyAggregator);
	

	topologyHelper.Install(nodeContainer);
	topologyHelper.PlaceObstacle(30);



	//senderPhy
	AnimationInterface animInterface("sim.xml");
	Simulator::Stop(Seconds(10.0));

	Simulator::Run();

	Simulator::Destroy();
}