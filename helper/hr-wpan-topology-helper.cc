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

namespace ns3
{
	namespace HrWpan
	{

		TopologyHelper::TopologyHelper(double max_x, double max_y)
		{
			m_randomRectanglePositionAllocator = CreateObject<RandomRectanglePositionAllocator>();
			m_uRandomVar_x = CreateObject<UniformRandomVariable>();
			m_uRandomVar_y = CreateObject<UniformRandomVariable>();
			m_topologyAggregator = CreateObject<TopologyAggregator>();

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));

			m_uRandomVar_x->SetAttribute("Max", DoubleValue(max_x));
			m_uRandomVar_x->SetAttribute("Min", DoubleValue(0));
			
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

	} // namespace HrWpan

} // namepsace ns3