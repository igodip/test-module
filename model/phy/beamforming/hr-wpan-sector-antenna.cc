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
#include <ns3/double.h>

#include <cmath>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::SectorAntenna");

	namespace HrWpan
	{

		NS_OBJECT_ENSURE_REGISTERED(SectorAntenna);

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
				AddConstructor<SectorAntenna>().
				AddAttribute("Orientation", "The orientation of the Antenna (radians)",
					DoubleValue(0),
					MakeDoubleAccessor(&SectorAntenna::m_orientation),
					MakeDoubleChecker<double>()).
				AddAttribute("Beamwidth", 
					"The width of the beam (radians)",
					DoubleValue(DegreesToRadians(10)),
					MakeDoubleAccessor(&SectorAntenna::m_beamwidth),
					MakeDoubleChecker<double>()).
				AddAttribute("Gain",
					"The gain inside the main cone in dbm",
					DoubleValue(30),
					MakeDoubleAccessor(&SectorAntenna::m_gain),
					MakeDoubleChecker<double>()).
				AddAttribute("Loss",
					"The loss outside the main cone in dbm",
					DoubleValue(-30),
					MakeDoubleAccessor(&SectorAntenna::m_loss),
					MakeDoubleChecker<double>());

			return tid;
		}

		double SectorAntenna::GetGainDb(Angles a)
		{

			NS_LOG_FUNCTION(this<<a);

			double phi = a.phi - m_orientation;

			NS_LOG_INFO("Phi = " << phi);

			// make sure phi is in (-pi, pi]
			while (phi <= -M_PI)
			{
				phi += M_PI + M_PI;
			}
			while (phi > M_PI)
			{
				phi -= M_PI + M_PI;
			}

			NS_LOG_LOGIC("phi = " << phi);

			if (phi <= m_beamwidth / double(2) && phi >= -m_beamwidth / double(2))
			{
				return m_gain;
			}

			return m_loss;
			
		}

	} // HrWpan namespace

} // ns3 namespace