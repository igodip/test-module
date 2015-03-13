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

#include "hr-wpan-topology-aggregator.h"
#include <ns3/hr-wpan-link.h>
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::TopologyAggregator");

	//NS_OBJECT_ENSURE_REGISTERED(HrWpan::TopologyAggregator);

	namespace HrWpan
	{
		
		TopologyAggregator::TopologyAggregator()
		{
			NS_LOG_FUNCTION(this);
		}

		void TopologyAggregator::addLine(Ptr<Line> line)
		{
			NS_LOG_FUNCTION(this);

			/*Ptr<Link> link = DynamicCast<Ptr<Link>>(line);

			if (link != 0)
			{
				m_nodes_map[link->GetSender()] = link;
				m_nodes_map[link->GetReceiver()] = link;
			}*/

			m_lines.push_back(line);
		}

		TypeId TopologyAggregator::GetTypeId()
		{
		
			static TypeId tid = TypeId("TopologyAggregator")
				.SetParent<Object>()
				.AddConstructor<TopologyAggregator>();
			return tid;
		}

		const std::list<Ptr<Line> > & TopologyAggregator::getContainer() const
		{
			NS_LOG_FUNCTION(this);

			return m_lines;
		}

		Ptr<Line> TopologyAggregator::getLineByNode(Ptr<Node> node) const
		{
			return 0;
		}

	} // namespace HrWpan

} // namespace ns3
