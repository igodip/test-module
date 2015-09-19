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
#include <ns3/log.h>


namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanLine");

	namespace HrWpan
	{

		Line::Line() :
			m_start(0, 0, 0), m_end(0, 0, 0)
		{
			NS_LOG_FUNCTION(this);
		}

		Line::Line(double start_x, double start_y, double end_x, double end_y) :
			m_start(start_x, start_y, 0), m_end(end_x, end_y, 0)
		{
			NS_LOG_FUNCTION(this);
		}

		TypeId Line::GetTypeId()
		{

			static TypeId tid = TypeId("HrWpan::Line").
				SetParent<Object>().
				AddConstructor<Line>();

			return tid;
		}

		void Line::DoDispose()
		{
			NS_LOG_FUNCTION(this);
		}

		void Line::setStart(const Vector3D & start)
		{
			m_start = start;
		}

		void Line::setEnd(const Vector3D & end)
		{
			m_end = end;
		}

		Vector3D Line::getStart() 
		{
			return m_start;
		}

		Vector3D Line::getEnd() 
		{
			return m_end;
		}

	} // namespace HrWpan

} // namespace ns3