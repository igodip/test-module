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

#include "hr-wpan-obstacle.h"
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpan::Obstacle");

	namespace HrWpan
	{
		Obstacle::Obstacle() :
			Line()
		{
			NS_LOG_FUNCTION(this);
		}

		Obstacle::Obstacle(double start_x, double start_y, double end_x,
			double end_y) :
			Line(start_x,start_y,end_x,end_y)
		{
			NS_LOG_FUNCTION(this);
		}

		TypeId Obstacle::GetTypeId(void)
		{
			static TypeId tid = TypeId("HrWpan::Obstacle").
				SetParent<Line>().
				AddConstructor<Obstacle>();

			return tid;
		}

		void Obstacle::DoDispose()
		{
			Line::DoDispose();
		}

		Obstacle::~Obstacle()
		{
			NS_LOG_FUNCTION(this);
		}

	} //HrWpan

} // ns3