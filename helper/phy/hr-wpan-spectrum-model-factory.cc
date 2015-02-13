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

#include "hr-wpan-spectrum-model-factory.h"
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanSpectrumModelFactory");

	HrWpanSpectrumModelFactory& HrWpanSpectrumModelFactory::getInstance(void)
	{
		
		static HrWpanSpectrumModelFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;

	}

	HrWpanSpectrumModelFactory::HrWpanSpectrumModelFactory(void)
	{

		NS_LOG_FUNCTION(this);
		createBands();

	}

	void HrWpanSpectrumModelFactory::createBands(void)
	{
		NS_LOG_FUNCTION(this);
		Bands bands;
		//Figure 96 IEEE 802.15.3c
		// 3 Mhz resolution, with the center frequency from 57.24 GHz 
		// to 65.88 GHz
		
		for (int i = -1; i < 2880; i++)
		{
			BandInfo bi;
			
			bi.fl = 57240.0e6 + i * 3.0e6;
			bi.fh = 57240.0e6 + (i+1)*3.0e6;
			bi.fc = (bi.fl + bi.fh) / 2;

			bands.push_back(bi);
		}

		m_ptrSpectrumModel = Create<SpectrumModel>(bands);
	}

}