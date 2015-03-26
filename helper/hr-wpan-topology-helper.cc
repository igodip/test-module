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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-topology-helper.h"

#include <ns3/log.h>
#include <ns3/double.h>
#include <ns3/assert.h>
#include <ns3/abort.h>

#include <ns3/hr-wpan-link.h>
#include <ns3/hr-wpan-obstacle.h>
#include <ns3/mobility-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/node-container.h>

#include <ns3/hr-wpan-sector-antenna.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/on-off-helper.h>
#include <ns3/internet-module.h>
#include <ns3/packet-sink-helper.h>

#include <cmath>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpan::TopologyHelper");

	namespace HrWpan
	{

		TopologyHelper::TopologyHelper(double max_x, double max_y, double obs_max_size,Ptr<TopologyAggregator> topologyAggregator)
		{
			NS_LOG_FUNCTION(this << max_x << max_y);

			m_randomRectanglePositionAllocator = CreateObject<RandomRectanglePositionAllocator>();
			m_uRandomVar_x = CreateObject<UniformRandomVariable>();
			m_uRandomVar_y = CreateObject<UniformRandomVariable>();
			m_uRandomSize = CreateObject<UniformRandomVariable>();
			m_uRandomOrientation = CreateObject<UniformRandomVariable>();
			m_topologyAggregator = topologyAggregator;

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));
			
			m_uRandomOrientation->SetAttribute("Max", DoubleValue(2 * M_PI));
			m_uRandomOrientation->SetAttribute("Min", DoubleValue(0));

			NS_ASSERT(obs_max_size > 0);
			
			m_uRandomSize->SetAttribute("Max", DoubleValue(obs_max_size));
			m_uRandomSize->SetAttribute("Min", DoubleValue(0));

			m_randomRectanglePositionAllocator->SetX(m_uRandomVar_x);
			m_randomRectanglePositionAllocator->SetY(m_uRandomVar_y);

			
		}

		TopologyHelper::~TopologyHelper()
		{
			NS_LOG_FUNCTION(this);

			m_randomRectanglePositionAllocator->Dispose();
			m_uRandomVar_x->Dispose();
			m_uRandomVar_y->Dispose();

			m_randomRectanglePositionAllocator = 0;
			m_uRandomVar_x = 0;
			m_uRandomVar_y = 0;
			m_topologyAggregator = 0;
		}

		void TopologyHelper::PlaceNodesPair(Ptr<Node> sender, Ptr<Node> receiver)
		{
			
			NS_LOG_FUNCTION(this << sender << receiver);

			Vector sender_point;
			Vector receiver_point;

			NS_LOG_INFO("Placing a link");

			sender_point = m_randomRectanglePositionAllocator->GetNext();
			receiver_point = m_randomRectanglePositionAllocator->GetNext();
			
			addPosition(sender, sender_point);
			addPosition(receiver, receiver_point);

			Ptr<Link> link = CreateObject<Link>();
			
			link->SetSender(sender);
			link->SetReceiver(receiver);

			steerAntennas(link);

			//Just add 
			Ptr<HrWpanNetDevice> senderDev = DynamicCast<HrWpanNetDevice>(sender->GetDevice(0));
			Ptr<HrWpanNetDevice> receiverDev = DynamicCast<HrWpanNetDevice>(receiver->GetDevice(0));

			senderDev->GetPhy()->TxOn();
			receiverDev->GetPhy()->RxOn();
			
			m_topologyAggregator->addLine(link);

		}

		void TopologyHelper::PlaceObstacle()
		{

			NS_LOG_FUNCTION(this);

			Vector start_point;
			Vector end_point;
			Vector center_point;

			Ptr<Obstacle> obstacle = CreateObject<Obstacle>();

			NS_LOG_INFO("Placing obstacle");

			double orientation = m_uRandomOrientation->GetValue();
			double size = m_uRandomSize->GetValue();

			double xdiff = cos(orientation)*(size / double(2));
			double ydiff = cos(orientation)*(size / double(2));

			center_point = m_randomRectanglePositionAllocator->GetNext();

			start_point.x = center_point.x + xdiff;
			start_point.y = center_point.y + ydiff;
			start_point.z = 0;

			end_point.x = center_point.x - xdiff;
			end_point.y = center_point.y - ydiff;
			end_point.z = 0;

			obstacle->setStart(start_point);
			obstacle->setEnd(end_point);

			m_topologyAggregator->addLine(obstacle);
			
		}

		void TopologyHelper::Install(NodeContainer c)
		{
			NS_LOG_FUNCTION(this);

			NS_ASSERT(c.GetN() % 2 == 0);

			for (NodeContainer::Iterator i = c.Begin(); i != c.End();)
			{
				Ptr<Node> sender = *(i);
				i++;
				Ptr<Node> receiver = *(i);
				i++;
				PlaceNodesPair(sender, receiver);
			}
		}

		void TopologyHelper::PlaceObstacle(uint32_t num)
		{
			NS_LOG_FUNCTION(this << num);


			for (uint32_t i = 0; i < num; i++)
			{
				
				PlaceObstacle();

			}
		}

		void TopologyHelper::addPosition(Ptr<Node> node, Vector3D vec)
		{
			Ptr<Object> object = node;
			Ptr<MobilityModel> model = object->GetObject<MobilityModel>();

			NS_LOG_FUNCTION(node << vec);

			if (model == 0)
			{
				Ptr<ConstantPositionMobilityModel> positionMobilityModel =
					CreateObject<ConstantPositionMobilityModel>();
				NS_LOG_DEBUG("node=" << object);

				model = positionMobilityModel;

				node->AggregateObject(positionMobilityModel);

			}

			model->SetPosition(vec);
			NS_LOG_DEBUG("node=" << object);
		}

		bool TopologyHelper::intersect(Ptr<Line> a, Ptr<Line> b)
		{
			return get_line_intersection(a->getStart().x,a->getStart().y,
				a->getEnd().x,a->getEnd().y,
				b->getStart().x,b->getStart().y,
				b->getEnd().x, b->getEnd().y
				) == 1;
		}

		char TopologyHelper::get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y,
			double p2_x, double p2_y, double p3_x, double p3_y)
		{
			double s1_x, s1_y, s2_x, s2_y;
			s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
			s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

			double s, t;
			s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
			t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

			if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
			{
				/*
				// Collision detected
				if (i_x != NULL)
					*i_x = p0_x + (t * s1_x);
				if (i_y != NULL)
					*i_y = p0_y + (t * s1_y);
				*/
				return 1;
			}

			return 0; // No collision
		}

		void TopologyHelper::steerAntennas(Ptr<Link> link)
		{
			NS_LOG_FUNCTION_NOARGS();

			Ptr<Node> sender = link->GetSender();
			Ptr<Node> receiver = link->GetReceiver();

			Ptr<HrWpanNetDevice> senderDev = DynamicCast<HrWpanNetDevice>(sender->GetDevice(0));
			Ptr<HrWpanNetDevice> receiverDev = DynamicCast<HrWpanNetDevice>(receiver->GetDevice(0));

			NS_ASSERT_MSG(senderDev != 0 || receiverDev != 0,"No HrWpanNetDevice");

			Ptr<SectorAntenna> senderAntenna = DynamicCast<SectorAntenna>(senderDev->GetPhy()->GetRxAntenna());
			Ptr<SectorAntenna> receiverAntenna = DynamicCast<SectorAntenna>( receiverDev->GetPhy()->GetRxAntenna());

			Vector senderPos = sender->GetObject<MobilityModel>()->GetPosition();
			Vector receiverPos = receiver->GetObject<MobilityModel>()->GetPosition();

			double deltax = receiverPos.x - senderPos.x;
			double deltay = receiverPos.y - senderPos.y;

			double angle = atan2(deltay, deltax);

			NS_LOG_INFO("Angle = " << angle);

			senderAntenna->SetAttribute("Orientation", DoubleValue(angle));
			senderAntenna->SetAttribute("Beamwidth", DoubleValue(DegreesToRadians(3)));
			receiverAntenna->SetAttribute("Orientation", DoubleValue(angle+M_PI));
			senderAntenna->SetAttribute("Beamwidth", DoubleValue(DegreesToRadians(3)));

		}

		void TopologyHelper::InstallApplication()
		{
			const std::list<Ptr<Line> > lines = m_topologyAggregator->getContainer();

			std::list<Ptr<Line> >::const_iterator it = lines.begin();
			
			Ptr<UniformRandomVariable> uRandVar = CreateObject<UniformRandomVariable>();

			uRandVar->SetAttribute("Min", DoubleValue(0.0));
			uRandVar->SetAttribute("Max", DoubleValue(1.0));

			while (it != lines.end())
			{
				Ptr<Link> link = DynamicCast<Link>(*it);

				if (link != 0)
				{

					Ptr<Node> sender = link->GetSender();
					Ptr<Node> receiver = link->GetReceiver();

					Ipv4Address senderIpv4 = sender->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();
					Ipv4Address receiverIpv4 = receiver->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();

					Mac48Address receiverMac = Mac48Address::ConvertFrom(receiver->GetDevice(0)->GetAddress());
					Mac48Address senderMac = Mac48Address::ConvertFrom(sender->GetDevice(0)->GetAddress());
				
					OnOffHelper onoff("ns3::UdpSocketFactory",
						Address(InetSocketAddress(receiverIpv4, 15)));
					onoff.SetConstantRate(DataRate("512kb/s"));
					
					//double spost = uRandVar->GetValue()
					
					ApplicationContainer app = onoff.Install(sender);
					
					app.Start(Seconds(1.0));
					app.Stop(Seconds(10.0));

					PacketSinkHelper sink("ns3::UdpSocketFactory",
						Address(InetSocketAddress(Ipv4Address::GetAny(), 15)));

					app = sink.Install(receiver);
					app.Start(Seconds(1.0));
					app.Stop(Seconds(10.0));

					//Populate arp cache
					Ptr<ArpCache> arpSender = sender->GetObject<Ipv4L3Protocol>()->GetInterface(1)->GetArpCache();
					Ptr<ArpCache> arpReceiver = receiver->GetObject<Ipv4L3Protocol>()->GetInterface(1)->GetArpCache();
	
					ArpCache::Entry *entry = arpSender->Add(receiverIpv4);
					entry->MarkWaitReply(0);
					entry->MarkAlive(receiverMac);

					ArpCache::Entry *entry2 = arpReceiver->Add(senderIpv4);
					entry2->MarkWaitReply(0);
					entry2->MarkAlive(senderMac);

				}

				++it;
			}

		}

	} // namespace HrWpan

} // namepsace ns3