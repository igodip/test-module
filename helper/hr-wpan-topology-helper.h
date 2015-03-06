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

#ifndef HR_WPAN_TOPOLOGY_HELPER_H
#define HR_WPAN_TOPOLOGY_HELPER_H

#include <ns3/pointer.h>
#include <ns3/position-allocator.h>
#include <ns3/node.h>
#include <ns3/hr-wpan-topology-aggregator.h>

namespace ns3
{
	namespace HrWpan
	{

		class TopologyHelper
		{
		public:
			
			TopologyHelper(double max_x, double max_y);
			~TopologyHelper();

			void PlaceNodesPair(Ptr<Node> sender, Ptr<Node> receiver);
			void PlaceObstacle();

		protected:

			Ptr<RandomRectanglePositionAllocator> m_randomRectanglePositionAllocator;
			Ptr<UniformRandomVariable> m_uRandomVar_x;
			Ptr<UniformRandomVariable> m_uRandomVar_y;

			Ptr<TopologyAggregator> m_topologyAggregator;

		private:

			Vector2D convertTo2D(Vector3D);

		};

	} // namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_TOPOLOGY_HELPER_H