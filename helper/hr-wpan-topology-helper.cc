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

#include <ns3/hr-wpan-link.h>
#include <ns3/hr-wpan-obstacle.h>
#include <ns3/mobility-model.h>

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
			
			bool intersect_flag = false;
			const std::list< Ptr<Line> > &  lines = m_topologyAggregator->getContainer();

			do {

				intersect_flag = false;

				Vector sender_point = m_randomRectanglePositionAllocator->GetNext();
				Vector receiver_point = m_randomRectanglePositionAllocator->GetNext();

				Line line = Line();

				line.setStart(sender_point);
				line.setEnd(receiver_point);

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

					if (intersect(obstacle, &line))
					{
						intersect_flag = true;
					}

					++start_it;
				}

			} while (intersect_flag);

			//Assign position to nodes
			
			

			//Store the line

		}

		void TopologyHelper::PlaceObstacle()
		{

			bool intersect_flag = false;
			const std::list< Ptr<Line> > &  lines = m_topologyAggregator->getContainer();

			do
			{

				//Generate two random points

				Vector start_point = m_randomRectanglePositionAllocator->GetNext();
				Vector end_point = m_randomRectanglePositionAllocator->GetNext();

				std::list<Ptr<Line > >::const_iterator start_it = lines.begin();
				std::list<Ptr< Line > >::const_iterator end_it = lines.end();

				Line line = Line();

				line.setStart(start_point);
				line.setEnd(end_point);

				while (start_it != end_it && !intersect_flag)
				{

					++start_it;

					Ptr<Link> link = DynamicCast<Link>(*start_it);

					if (link == 0)
					{
						continue;
					}

				}
				
				lines.begin();

				intersect_flag = false;
						

			} while (intersect_flag);


			
			//No intersections place the line, otherwise repeat!
		
		}

		void TopologyHelper::addPosition(Ptr<Node> node, Vector3D vec)
		{
			Ptr<Object> object = node;
			Ptr<MobilityModel> model = object->GetObject<MobilityModel>();
			if (model == 0)
			{
				object->AggregateObject(hierarchical);
				NS_LOG_DEBUG("node=" << object << ", mob=" << hierarchical);
				
			}
			Vector position = m_position->GetNext();
			model->SetPosition(position);
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