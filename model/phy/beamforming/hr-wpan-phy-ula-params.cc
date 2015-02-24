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

#include "hr-wpan-phy-ula-params.h"
#include <ns3/log.h>
#include <ns3/angles.h>
#include <cmath>

namespace ns3 {

	HrWpanPhyUlaParams::HrWpanPhyUlaParams()
	{
		m_orientation =0;
		m_beamwidth = M_PI/2;
	}

	HrWpanPhyUlaParams::HrWpanPhyUlaParams(double orientation, double beamwidth) 		
	{
		m_orientation = DegreesToRadians(orientation);
		m_beamwidth = DegreesToRadians(beamwidth);
	}

	bool HrWpanPhyUlaParams::operator==(const HrWpanPhyUlaParams & s) const
	{
		if (s.m_beamwidth == m_beamwidth && s.m_orientation == m_orientation)
		{
			return true;
		}

		return false;
	}

}