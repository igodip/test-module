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

#ifndef HR_WPAN_PHY_ULA_ANTENNA_H
#define HR_WPAN_PHY_ULA_ANTENNA_H

#include <ns3/antenna-model.h>
#include <ns3/parabolic-antenna-model.h>

#include "hr-wpan-phy-ula-params.h"

namespace ns3
{

	class HrWpanPhyUlaAntenna : public AntennaModel
	{
		
	public:
		
		HrWpanPhyUlaAntenna(void);
		virtual ~HrWpanPhyUlaAntenna();

		static TypeId GetTypeId();

		virtual double GetGainDb(Angles a) ;

		/**
		 * \fn	void HrWpanPhyUlaAntenna::SetUlaParams(const HrWpanPhyUlaParams & ulaParams);
		 *
		 * \brief	Sets ula parameters.
		 *
		 * \param	ulaParams	A variable-length parameters list containing ula parameters.
		 */

		void SetUlaParams(const HrWpanPhyUlaParams & ulaParams);

		/**
		 * \fn	HrWpanPhyUlaParams HrWpanPhyUlaAntenna::GetUlaParams() const;
		 *
		 * \brief	Gets ula parameters.
		 * \return	The ula parameters.
		 */

		HrWpanPhyUlaParams GetUlaParams() const;

		/**
		 * \fn	void HrWpanPhyUlaAntenna::SetOrientation(double orientation);
		 *
		 * \brief	Sets an orientation.
		 * \param	orientation	The orientation in degrees.
		 */

		void SetOrientation(double orientation);

		/**
		 * \fn	double HrWpanPhyUlaAntenna::GetOrientation() const;
		 *
		 * \brief	Gets the orientation.
		 * \return	The orientation in degrees.
		 */

		double GetOrientation() const;

	protected:

		double m_startOrientation;

		HrWpanPhyUlaParams m_currentParams;

		ParabolicAntennaModel m_parabolicAntennaModel;

	};

}

#endif