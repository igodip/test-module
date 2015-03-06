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

namespace ns3
{
	namespace HrWpan
	{

		TopologyAggregator::TopologyAggregator()
		{
			
		}

		void TopologyAggregator::addLine(Ptr<Line> line)
		{
			m_lines.push_back(line);
		}

		TypeId TopologyAggregator::GetTypeId()
		{
			static TypeId tid = TypeId();
			return tid;
		}

	} // namespace HrWpan

} // namespace ns3
