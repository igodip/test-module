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

#include "hr-wpan-obstacle-propagation-model.h"
#include <ns3/string.h>
#include <ns3/pointer.h>
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanObstaclePropagationModel");

	namespace HrWpan
	{

		ObstaclePropagationLossModel::ObstaclePropagationLossModel()
		{

		}

		ObstaclePropagationLossModel::~ObstaclePropagationLossModel()
		{

		}

		TypeId	ObstaclePropagationLossModel::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::ObstaclePropagationLossModel")
				.SetParent<PropagationLossModel>()
				.AddConstructor<ObstaclePropagationLossModel>()
				;
			return tid;
		}

		double ObstaclePropagationLossModel::DoCalcRxPower(double txPowerDbm, Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
		{
			return 0;
		}

		int64_t ObstaclePropagationLossModel::DoAssignStreams(int64_t stream)
		{
			return 0;
		}

	}




}