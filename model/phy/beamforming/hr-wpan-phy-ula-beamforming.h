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

#ifndef HR_WPAN_PHY_ULA_BEAMFORMING
#define HR_WPAN_PHY_ULA_BEAMFORMING

#include "hr-wpan-phy-ula-params.h"
#include <ns3/object.h>
#include <vector>
#include <map>

namespace ns3
{
	class HrWpanPhyUlaBeamforming
	{

	public:

		static HrWpanPhyUlaBeamforming & GetInstance();
		virtual ~HrWpanPhyUlaBeamforming(void);
		//std::vector<const HrWpanPhyUlaBeamforming *> GetSectorsByODPNumber(const int i) const;
		//std::vector<const HrWpanPhyUlaBeamforming *> GetBeamBySectorNumber(const int i) const;

		const HrWpanPhyUlaParams * GetParamsBySectorNumber(const int odp,const int sector)const;
		const HrWpanPhyUlaParams * GetParamsByOdpNumber(const int odp) const;



	protected:

		HrWpanPhyUlaBeamforming();

		HrWpanPhyUlaBeamforming(HrWpanPhyUlaBeamforming const &);
		void operator = (HrWpanPhyUlaBeamforming const &);

	private:

		uint8_t m_sectorsNumber;
		uint8_t m_odpNumber;
		uint8_t m_beamsNumber;

		uint8_t m_maxLeaves;

		std::map<int, const HrWpanPhyUlaParams *> params;

	};
}

#endif