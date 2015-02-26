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
#include <ns3/packet.h>
#include <ns3/hr-wpan-phy.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/simulator.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/propagation-loss-model.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrExampleMacLayer");

void SendOnePacket(Ptr<HrWpanMac> sender, Ptr<HrWpanMac> receiver)
{
	uint32_t n = 10;
	Ptr<Packet> p = Create<Packet>(n);
	sender->McpsDataRequest(p);
}

int main(int argc, char ** argv)
{

	LogComponentEnableAll(LOG_PREFIX_FUNC);
	LogComponentEnable("HrWpanPhy", LOG_LEVEL_ALL);
	LogComponentEnable("HrWpanMac", LOG_LEVEL_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);

	Ptr<SingleModelSpectrumChannel> channel = CreateObject<SingleModelSpectrumChannel>();
	Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();

	Ptr<HrWpanPhy> senderPhy = CreateObject<HrWpanPhy>();
	Ptr<HrWpanPhy> receiverPhy = CreateObject<HrWpanPhy>();

	Ptr<HrWpanMac> senderMac = CreateObject<HrWpanMac>();
	Ptr<HrWpanMac> receiverMac = CreateObject<HrWpanMac>();

	NS_LOG_INFO("Hey man!");
	senderPhy->SetPhyUser(senderMac->GetPointer());
	senderMac->SetPhyProvider(senderPhy->GetPointer());
	receiverPhy->SetPhyUser(receiverMac->GetPointer());
	receiverMac->SetPhyProvider(receiverPhy->GetPointer());

	channel->AddPropagationLossModel(lossModel);
	channel->AddRx(senderPhy);
	channel->AddRx(receiverPhy);

	NS_LOG_INFO("Hey asdh");
	//Setting channel
	senderPhy->SetChannel(channel);
	receiverPhy->SetChannel(channel);

	//senderPhy
	Simulator::Stop(Seconds(10.0));

	Simulator::Schedule(Seconds(1.0), &SendOnePacket, senderMac, receiverMac);

	Simulator::Run();

	Simulator::Destroy();

	return 0;
}