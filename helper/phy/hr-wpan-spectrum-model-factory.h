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

#include <ns3/spectrum-value.h>
#include <ns3/log.h>

namespace ns3 {

	class HrWpanSpectrumModelFactory {
	public:
		static HrWpanSpectrumModelFactory& getInstance(void);
		Ptr<SpectrumModel> getSpectrumModel(void);

	private:

		HrWpanSpectrumModelFactory(void);
		void createBands(void);

		Ptr<SpectrumModel> m_ptrSpectrumModel;


	};

	

}