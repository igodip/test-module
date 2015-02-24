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

#include "hr-wpan-phy-ula-antenna.h"
#include <ns3/log.h>
#include <cmath>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanPhyUlaAntenna");

	NS_OBJECT_ENSURE_REGISTERED(HrWpanPhyUlaAntenna);

	HrWpanPhyUlaAntenna::HrWpanPhyUlaAntenna(void)
	{
		NS_LOG_FUNCTION(this);
	}

	HrWpanPhyUlaAntenna::~HrWpanPhyUlaAntenna()
	{
		NS_LOG_FUNCTION(this);
	}

	void HrWpanPhyUlaAntenna::SetUlaParams(const HrWpanPhyUlaParams & ulaParams)
	{
		NS_LOG_FUNCTION(this);

		m_currentParams = ulaParams;

		//Change the antenna orientation also
		
		double newOrientation = fmod(m_startOrientation + ulaParams.m_orientation, 2*M_PI);

		
		m_parabolicAntennaModel.SetOrientation(newOrientation);
		m_parabolicAntennaModel.SetBeamwidth(ulaParams.m_beamwidth);

	}

	HrWpanPhyUlaParams HrWpanPhyUlaAntenna::GetUlaParams(void) const
	{
		NS_LOG_FUNCTION(this);

		return m_currentParams;
	}

	TypeId HrWpanPhyUlaAntenna::GetTypeId() 
	{
		static TypeId tid = TypeId("ns3::HrWpanPhyUlaAntenna").
			SetParent<Object>().
			AddConstructor<HrWpanPhyUlaAntenna>();

		return tid;
	}

	double HrWpanPhyUlaAntenna::GetGainDb(Angles a)
	{

		return m_parabolicAntennaModel.GetGainDb(a);
	}

	void HrWpanPhyUlaAntenna::SetOrientation(double orientation)
	{
		m_startOrientation = DegreesToRadians(orientation);
	}

	double HrWpanPhyUlaAntenna::GetOrientation() const
	{
		return RadiansToDegrees(m_startOrientation);
	}
}