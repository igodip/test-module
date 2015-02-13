/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2015
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
* Author: Igor Di Paolo <igor.di.paolo>
*
*/

#include "hr-wpan-spectrum-value-helper.h"
#include "hr-wpan-spectrum-model-factory.h"

#include <ns3/log.h>
#include <ns3/spectrum-value.h>

#include <cmath>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanSpectrumValueHelper");

	HrWpanSpectrumValueHelper::HrWpanSpectrumValueHelper()
	{
		NS_LOG_FUNCTION(this);
		m_noiseFactor = 1.0;
	}
	
	HrWpanSpectrumValueHelper::~HrWpanSpectrumValueHelper()
	{
		NS_LOG_FUNCTION(this);
	}

	Ptr<SpectrumValue> HrWpanSpectrumValueHelper::CreateTxPowerSpectralDensity(double txPower, uint32_t channel) {

		NS_LOG_FUNCTION(this);
		Ptr<SpectrumValue> txPsd = Create<SpectrumValue>(HrWpanSpectrumModelFactory::getInstance().getSpectrumModel());

		//txPower is expressed in dBm. We must convert it into natural unit (W).
		txPower = pow(10, (txPower - 30) / 10);

		//The effective occupied bandwidth of the signal si modelled to be 2 Mhz.
		//double txPowerDensity = txPower / 2.0e6;

		// 4 channels
		// 1 58.320 centered 2.16 GHz large
		// 2 60.480 centered 2.16 GHz large
		// 3 62.640 centered 2.16 GHz large
		// 4 64.800 centered 2.16 GHz large
		
		NS_ASSERT_MSG((channel >= 1 && channel <= 4), "Invalid channel numbers");

		



		return txPsd;
	}

	Ptr<SpectrumValue> HrWpanSpectrumValueHelper::CreateNoisePowerSpectralDensity(uint32_t channel) {

		NS_LOG_FUNCTION(this);
		Ptr<SpectrumValue> noisePsd = Create<SpectrumValue>(HrWpanSpectrumModelFactory::getInstance().getSpectrumModel());

		//static const double BOLTZMANN = 1.3803e-23;
		// Nt  is the power of thermal noise in W
		//double Nt = BOLTZMANN * 290.0;
		// noise Floor (W) which accounts for thermal noise and non-idealities of the receiver
		//double noisePowerDensity = m_noiseFactor * Nt;

		NS_ASSERT_MSG((channel >= 1 && channel <= 4), "Invalid channel numbers");

		return noisePsd;

	}

	double HrWpanSpectrumValueHelper::TotalAvgPower(Ptr<const SpectrumValue> psd, uint32_t channel)
	{

		NS_LOG_FUNCTION(psd);
		double totalAvgPower = 0.0;

		NS_ASSERT(psd->GetSpectrumModel() == HrWpanSpectrumModelFactory::getInstance().getSpectrumModel());

		//numerically integrate to get 
		
		totalAvgPower *= 3.0e6;

		return totalAvgPower;
	}

}