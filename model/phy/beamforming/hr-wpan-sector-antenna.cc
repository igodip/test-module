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

#include "hr-wpan-sector-antenna.h"

#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::SectorAntenna");

	namespace HrWpan
	{
		SectorAntenna::SectorAntenna()
		{
			NS_LOG_FUNCTION(this);
		}

		SectorAntenna::~SectorAntenna()
		{
			NS_LOG_FUNCTION(this);
		}

		TypeId SectorAntenna::GetTypeId()
		{
			NS_LOG_FUNCTION_NOARGS();

			static TypeId tid = TypeId("ns3::HrWpan::SectorAntenna").
				SetParent<AntennaModel>().
				AddConstructor<SectorAntenna>();

			return tid;
		}

		double SectorAntenna::GetGainDb(Angles a)
		{
			return 0;
			
		}

		void SectorAntenna::SetOrientation(double orientation)
		{
			m_startOrientation = DegreesToRadians(orientation);
		}

		double SectorAntenna::GetOrientation() const
		{
			return RadiansToDegrees(m_startOrientation);
		}
	} // HrWpan namespace

} // ns3 namespace