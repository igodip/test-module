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

#ifndef HR_WPAN_SECTOR_ANTENNA_H
#define HR_WPAN_SECTOR_ANTENNA_H

#include <ns3/antenna-model.h>

namespace ns3
{

	namespace HrWpan
	{

		class SectorAntenna : public AntennaModel
		{
		public:

			SectorAntenna(void);
			virtual ~SectorAntenna();

			static TypeId GetTypeId();

			virtual double GetGainDb(Angles a);

			void SetOrientation(double orientation);

			double GetOrientation() const;

		protected:

			double m_startOrientation; // degrees
			double m_beamwidth; // degrees
			double m_loss;

		};

	} // namespace HrWpan

} // namespace ns3



#endif //HR_WPAN_SECTOR_ANTENNA_H