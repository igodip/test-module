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
#include <ns3/object.h>
#include <ns3/node.h>
#include "hr-wpan-line.h"

namespace ns3
{
	namespace HrWpan
	{

		class TopologyAggregator : public Object
		{
		public:
			static TypeId GetTypeId();

			TopologyAggregator();
			void addLine(Ptr<Line> line);
			const std::list<Ptr<Line> > & getContainer() const;
			Ptr<Line>  getLineByNode(Ptr<Node> node) const;

		protected:

			std::list<Ptr<Line> > m_lines;
			std::map<Ptr<Node>, Ptr<Line> > m_nodes_map;

		};

	} // namespace HrWpan

} // namespace ns3

#endif