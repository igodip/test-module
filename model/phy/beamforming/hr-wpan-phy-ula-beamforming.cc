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

#include "hr-wpan-phy-ula-beamforming.h"
#include <ns3/assert.h>
#include <ns3/log.h>
#include <cmath>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpanPhyUlaBeamforming");

	HrWpanPhyUlaBeamforming & HrWpanPhyUlaBeamforming::GetInstance()
	{
		static HrWpanPhyUlaBeamforming instance;
		return instance;
	}

	HrWpanPhyUlaBeamforming::HrWpanPhyUlaBeamforming()
	{
		NS_LOG_FUNCTION(this);

		m_odpNumber = 2;
		m_sectorsNumber = 3;
		m_beamsNumber = 6;

		m_maxLeaves = 10; //TODO: Runtime max between odp, sectors and beams

		//ODP
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(1, new HrWpanPhyUlaParams(45, 90)));
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(2, new HrWpanPhyUlaParams(315,90)));

		//
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(10, new HrWpanPhyUlaParams(285, 30)));
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(11, new HrWpanPhyUlaParams(315, 30)));
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(12, new HrWpanPhyUlaParams(345, 30)));

		//
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(20, new HrWpanPhyUlaParams(15, 30)));
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(21, new HrWpanPhyUlaParams(45, 30)));
		params.insert(std::map< int, const HrWpanPhyUlaParams *>::value_type(22, new HrWpanPhyUlaParams(75, 30)));

	}

	HrWpanPhyUlaBeamforming::~HrWpanPhyUlaBeamforming()
	{
		NS_LOG_FUNCTION(this);

		for (std::map<int, const HrWpanPhyUlaParams *>::iterator it = params.begin(); it != params.end(); ++it)
			delete it->second;

	}

	const HrWpanPhyUlaParams * HrWpanPhyUlaBeamforming::GetParamsBySectorNumber(const int odp, const int sector) const
	{
		NS_LOG_FUNCTION(this << odp << sector);

		NS_ASSERT(odp > 0 && odp <= m_odpNumber);

		NS_ASSERT(sector > 0 && sector <= m_sectorsNumber);

		int pos = odp*m_maxLeaves + sector - 1;

		return params.find(pos)->second;

	}

	const HrWpanPhyUlaParams * HrWpanPhyUlaBeamforming::GetParamsByOdpNumber(const int odp) const
	{
		NS_LOG_FUNCTION(this << odp);

		NS_ASSERT(odp > 0 && odp <= m_odpNumber);

		return params.find(odp)->second;
	}

	/*std::vector<const HrWpanPhyUlaBeamforming *> HrWpanPhyUlaBeamforming::GetSectorsByODPNumber(const int odp) const
	{
		NS_LOG_FUNCTION(this << odp);

	}

	std::vector<const HrWpanPhyUlaBeamforming *> HrWpanPhyUlaBeamforming::GetBeamBySectorNumber(const int i) const
	{
		NS_LOG_FUNCTION(this << i);

		return 
	}*/




}