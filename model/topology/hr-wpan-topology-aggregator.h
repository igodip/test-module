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

#ifndef HR_WPAN_TOPOLOGY_AGGREGATOR_H
#define HR_WPAN_TOPOLOGY_AGGREGATOR_H

#include <list>
#include <map>
#include <set>
#include <ns3/object.h>
#include <ns3/node.h>
#include "hr-wpan-line.h"
#include "hr-wpan-link.h"

namespace ns3
{
	namespace HrWpan
	{

		class TopologyAggregator : public Object
		{
		public:

			TopologyAggregator();

			static TypeId GetTypeId();
			//Singleton
			static TopologyAggregator & getInstance();

			void addLine(Ptr<Line> line);
			const std::list<Ptr<Line> > & getContainer() const;
			Ptr<Link> getLineByNode(Ptr<Node> node);

			void SetBeamwidth(double beamwidth);

			void clear();
			
			std::set<Ptr<Node > > GetSteeredReceivers(double senderOrientation);

		protected:

			std::list<Ptr<Line> > m_lines;
			std::map<Ptr<Node>, Ptr<Link> > m_nodes_map;
			std::multimap<double, Ptr<Node> > m_nodes_orient;
			double m_beamwidth; // Radiants

		};

	} // namespace HrWpan

} // namespace ns3

#endif //HR_WPAN_TOPOLOGY_AGGREGATOR_H