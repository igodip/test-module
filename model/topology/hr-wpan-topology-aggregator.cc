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
#include <ns3/log.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/hr-wpan-sector-antenna.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::TopologyAggregator");

	//NS_OBJECT_ENSURE_REGISTERED(HrWpan::TopologyAggregator);

	namespace HrWpan
	{
		
		TopologyAggregator & TopologyAggregator::getInstance()
		{
			static TopologyAggregator topologyAggregator;

			return topologyAggregator;
		}

		TopologyAggregator::TopologyAggregator()
		{
			NS_LOG_FUNCTION(this);
		}

		void TopologyAggregator::addLine(Ptr<Line> line)
		{
			NS_LOG_FUNCTION(this);

			Ptr<Link> link = DynamicCast<Link >(line);

			if (link != 0)
			{
				m_nodes_map[link->GetSender()] = link;
				m_nodes_map[link->GetReceiver()] = link;

				Ptr<HrWpanNetDevice> receiverDev = DynamicCast<HrWpanNetDevice>(link->GetReceiver()->GetDevice(0));

				NS_ASSERT_MSG(receiverDev != 0, "No HrWpanNetDevice");

				Ptr<SectorAntenna> receiverAntenna = DynamicCast<SectorAntenna>(receiverDev->GetPhy()->GetRxAntenna());

				m_nodes_orient.insert(
					std::pair<double, Ptr< Node > >(receiverAntenna->GetOrientation(), link->GetReceiver())
				);

			}

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

		Ptr<Link> TopologyAggregator::getLineByNode(Ptr<Node> node)
		{
			NS_LOG_FUNCTION(this << node);

			return m_nodes_map[node];
		}

		void TopologyAggregator::clear()
		{
			NS_LOG_FUNCTION(this);

			m_lines.clear();
			m_nodes_map.clear();
			m_beamwidth = 0;
			m_nodes_orient.clear();
		}

		std::set<Ptr<Node > > TopologyAggregator::GetSteeredReceivers(double senderOrientation)
		{
			NS_LOG_FUNCTION(this);
			
			std::set<Ptr<Node> > result;

			double module = 2 * M_PI;
			//NS_LOG_INFO(module);
			double low_limit = fmod( senderOrientation + M_PI - m_beamwidth / 2, module);
			double up_limit = fmod( senderOrientation + M_PI + m_beamwidth / 2, module);

			

			if (low_limit > up_limit)
			{
				
				std::multimap<double, Ptr<Node> >::iterator itlow1,itlow2, itup1, itup2;
				itlow1 = m_nodes_orient.lower_bound(0);
				itup1 = m_nodes_orient.upper_bound(up_limit);

				itlow2 = m_nodes_orient.lower_bound(low_limit);
				itup2 = m_nodes_orient.upper_bound(2 * M_PI);

				while (itlow1 != itup1)
				{
					result.insert(((*itlow1).second));
					++itlow1;
				}

				while (itlow2 != itup2)
				{
					result.insert(((*itlow2).second));
					++itlow2;
				}

			}
			else
			{

				std::multimap<double,Ptr<Node> >::iterator itlow, itup;
				itlow = m_nodes_orient.lower_bound(low_limit);
				itup = m_nodes_orient.upper_bound(up_limit);

				while (itlow != itup)
				{
					
					result.insert(((*itlow).second));
					++itlow;
				}

			}

			return result;

		}

		void TopologyAggregator::SetBeamwidth(double beamwidth)
		{
			m_beamwidth = beamwidth;
		}

	} // namespace HrWpan

} // namespace ns3
