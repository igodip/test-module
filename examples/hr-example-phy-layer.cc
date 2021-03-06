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
#include <ns3/simulator.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/propagation-loss-model.h>

#include <ns3/parabolic-antenna-model.h>

using namespace ns3;

uint16_t orientationReciever = 270;

NS_LOG_COMPONENT_DEFINE("HrExamplePhyLayer");

void SendOnePacket(Ptr<HrWpanPhy> sender, Ptr<HrWpanPhy> receiver, Ptr<ParabolicAntennaModel> ulaAntenna)
{
	uint32_t n = 10;
	Ptr<Packet> p = Create<Packet>(n);

	orientationReciever = (orientationReciever + 90) % 360;

	ulaAntenna->SetOrientation(orientationReciever);

	sender->SendMacPdu(p);
}


int main(int argc, char ** argv)
{
	LogComponentEnableAll(LOG_PREFIX_FUNC);
	//LogComponentEnable("HrWpanPhy", LOG_LEVEL_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);
	//LogComponentEnable("ParabolicAntennaModel", LOG_LEVEL_ALL);

	Ptr<HrWpanPhy> sender = CreateObject<HrWpanPhy>();
	Ptr<HrWpanPhy> receiver = CreateObject<HrWpanPhy>();

	Ptr<SingleModelSpectrumChannel> channel = CreateObject<SingleModelSpectrumChannel>();
	sender->SetChannel(channel);
	receiver->SetChannel(channel);

	Ptr<ParabolicAntennaModel> senderAntenna2 = CreateObject<ParabolicAntennaModel>();
	
	senderAntenna2->SetBeamwidth(3);
	senderAntenna2->SetOrientation(90);

	Ptr<ParabolicAntennaModel> receiverAntenna2 = CreateObject<ParabolicAntennaModel>();
	receiverAntenna2->SetBeamwidth(3);
	receiverAntenna2->SetOrientation(orientationReciever);

	receiver->SetAntenna(receiverAntenna2);
	sender->SetAntenna(senderAntenna2);

	Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();

	channel->AddPropagationLossModel(lossModel);
	channel->AddRx(sender);
	channel->AddRx(receiver);

	Ptr<ConstantPositionMobilityModel> senderMobility = CreateObject<ConstantPositionMobilityModel>();
	sender->SetMobility(senderMobility);

	Ptr<ConstantPositionMobilityModel> receiverMobility = CreateObject<ConstantPositionMobilityModel>();
	receiver->SetMobility(receiverMobility);

	Vector posReceiver = Vector(0, 2, 0);
	receiverMobility->SetPosition(posReceiver);

	Simulator::Stop(Seconds(10.0));

	Simulator::Schedule(Seconds(1.0), &SendOnePacket, sender, receiver,receiverAntenna2);
	Simulator::Schedule(Seconds(2.0), &SendOnePacket, sender, receiver, receiverAntenna2);
	Simulator::Schedule(Seconds(3.0), &SendOnePacket, sender, receiver, receiverAntenna2);
	Simulator::Schedule(Seconds(4.0), &SendOnePacket, sender, receiver, receiverAntenna2);

	Simulator::Run();

	Simulator::Destroy();

	return 0;

}
