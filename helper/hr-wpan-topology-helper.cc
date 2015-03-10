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

#include <ns3/hr-wpan-link.h>
#include <ns3/hr-wpan-obstacle.h>
#include <ns3/mobility-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/node-container.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpan::TopologyHelper");

	namespace HrWpan
	{

		TopologyHelper::TopologyHelper(double max_x, double max_y)
		{
			NS_LOG_FUNCTION(this << max_x << max_y);

			m_randomRectanglePositionAllocator = CreateObject<RandomRectanglePositionAllocator>();
			m_uRandomVar_x = CreateObject<UniformRandomVariable>();
			m_uRandomVar_y = CreateObject<UniformRandomVariable>();
			m_topologyAggregator = CreateObject<TopologyAggregator>();

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));

			m_randomRectanglePositionAllocator->SetX(m_uRandomVar_x);
			m_randomRectanglePositionAllocator->SetY(m_uRandomVar_y);
			
		}

		TopologyHelper::~TopologyHelper()
		{
			NS_LOG_FUNCTION(this);

			m_randomRectanglePositionAllocator->Dispose();
			m_uRandomVar_x->Dispose();
			m_uRandomVar_y->Dispose();
			m_topologyAggregator->Dispose();

			m_randomRectanglePositionAllocator = 0;
			m_uRandomVar_x = 0;
			m_uRandomVar_y = 0;
			m_topologyAggregator = 0;
		}

		void TopologyHelper::PlaceNodesPair(Ptr<Node> sender, Ptr<Node> receiver)
		{
			
			NS_LOG_FUNCTION(this << sender << receiver);

			bool intersect_flag = false;
			const std::list< Ptr<Line> > &  lines = m_topologyAggregator->getContainer();

			Ptr<Line> line = CreateObject<Line>();
			Vector sender_point;
			Vector receiver_point;

			do {

				NS_LOG_INFO("Trying to place a link");

				intersect_flag = false;

				sender_point = m_randomRectanglePositionAllocator->GetNext();
				receiver_point = m_randomRectanglePositionAllocator->GetNext();

				line->setStart(sender_point);
				line->setEnd(receiver_point);

				std::list<Ptr<Line > >::const_iterator start_it = lines.begin();
				std::list<Ptr<Line > >::const_iterator end_it = lines.end();

				while (start_it != end_it && !intersect_flag)
				{

					Ptr<Obstacle> obstacle = DynamicCast<Obstacle>(*start_it);

					if (obstacle == 0)
					{
						++start_it;
						continue;
					}

					if (intersect(obstacle, line))
					{
						intersect_flag = true;
					}

					++start_it;
				}

			} while (intersect_flag);

			//Assign position to nodes
			
			//addPosition(sender, sender_point);
			//addPosition(receiver, receiver_point);

			NS_LOG_INFO("Ciao");

			Ptr<Link> link = CreateObject<Link>();
			NS_LOG_INFO("Ciao");
			
			link->SetSender(sender);
			link->SetReceiver(receiver);

			//Store the line
			
			m_topologyAggregator->addLine(link);

		}

		void TopologyHelper::PlaceObstacle()
		{

			NS_LOG_FUNCTION(this);

			bool intersect_flag = false;
			const std::list< Ptr<Line> > &  lines = m_topologyAggregator->getContainer();

			Ptr<Line> line = CreateObject<Line>();
			Vector start_point;
			Vector end_point;

			std::list<Ptr<Line> >::const_iterator start_it = lines.begin();
			std::list<Ptr<Line> >::const_iterator end_it = lines.end();

			do
			{

				NS_LOG_INFO("Trying to place an obstacle");

				//Generate two random points

				start_point = m_randomRectanglePositionAllocator->GetNext();
				end_point = m_randomRectanglePositionAllocator->GetNext();

				line->setStart(start_point);
				line->setEnd(end_point);

				while (start_it != end_it && !intersect_flag)
				{

					Ptr<Link> link = DynamicCast<Link>(*start_it);

					if (link == 0)
					{
						++start_it;
						continue;
					}

					if (intersect(link, line))
					{
						intersect_flag = true;
					}

					++start_it;
				}

			} while (intersect_flag);

			Ptr<Obstacle> obstacle = CreateObject<Obstacle>();

			obstacle->setStart(start_point);
			obstacle->setEnd(end_point);

			line->Dispose();

			m_topologyAggregator->addLine(obstacle);
			
		}

		void TopologyHelper::Install(NodeContainer c)
		{
			NS_ASSERT(c.GetN() % 2 == 0);

			for (NodeContainer::Iterator i = c.Begin(); i != c.End();)
			{
				Ptr<Node> sender = *(++i);
				Ptr<Node> receiver = *(++i);
				PlaceNodesPair(sender, receiver);
			}
		}

		void TopologyHelper::PlaceObstacle(uint32_t num)
		{
			NS_ASSERT(num > 0);

			for (uint32_t i = 0; i < num; i++)
			{
				
				PlaceObstacle();

			}
		}

		void TopologyHelper::addPosition(Ptr<Node> node, Vector3D vec)
		{
			Ptr<Object> object = node;
			Ptr<MobilityModel> model = object->GetObject<MobilityModel>();

			if (model == 0)
			{
				Ptr<ConstantPositionMobilityModel> positionMobilityModel =
					CreateObject<ConstantPositionMobilityModel>();
				NS_LOG_DEBUG("node=" << object);

				model = positionMobilityModel;

				node->AggregateObject(positionMobilityModel);

			}

			model->SetPosition(vec);
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

	} // namespace HrWpan

} // namepsace ns3