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

#include "hr-wpan-line.h"

namespace ns3
{
	
	namespace HrWpan
	{

		Line::Line() :
			m_start(0, 0), m_end(0,0)
		{

		}

		Line::Line(double start_x, double start_y, double end_x, double end_y) :
			m_start(start_x, start_y), m_end(end_x,end_y)
		{

		}

		TypeId Line::GetTypeId()
		{
			static TypeId tid = TypeId("ns3::HrWpan::Line").
				AddConstructor<Line>();
			return tid;
		}

		void Line::DoDispose()
		{

		}

	} // namespace HrWpan

} // namespace ns3