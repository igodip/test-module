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

#ifndef HR_WPAN_OBSTACLE_PROPAGATION_MODEL_H
#define HR_WPAN_OBSTACLE_PROPAGATION_MODEL_H

#include <ns3/propagation-module.h>

namespace ns3
{

	namespace HrWpan
	{

		class ObstaclePropagationLossModel : public PropagationLossModel
		{
		public:
			/**
			* \brief Get the type ID.
			* \return the object TypeId
			*/
			static TypeId GetTypeId(void);

			ObstaclePropagationLossModel();
			virtual ~ObstaclePropagationLossModel();

		private:
			/**
			* \brief Copy constructor
			*
			* Defined and unimplemented to avoid misuse
			*/
			ObstaclePropagationLossModel(const ObstaclePropagationLossModel &);
			/**
			* \brief Copy constructor
			*
			* Defined and unimplemented to avoid misuse
			* \returns
			*/
			ObstaclePropagationLossModel & operator = (const ObstaclePropagationLossModel &);

			virtual double DoCalcRxPower(double txPowerDbm,
				Ptr<MobilityModel> a,
				Ptr<MobilityModel> b) const;

			virtual int64_t DoAssignStreams(int64_t stream);

			//Ptr<RandomVariableStream> m_variable; //!< random generator
		};

	} // namespace HrWpan

}// namespace ns3

#endif //HR_WPAN_OBSTACLE_PROPAGATION_MODEL_H