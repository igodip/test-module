/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2012 The Boeing Company
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
* Author: Gary Pei <guangyu.pei@boeing.com>
*/

#include "hr-wpan-spectrum-signal-parameters.h"
#include <ns3/log.h>
#include <ns3/packet-burst.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanSpectrumSignalParameters");

	HrWpanSpectrumSignalParameters::HrWpanSpectrumSignalParameters(void)
	{
		NS_LOG_FUNCTION(this);
	}

	HrWpanSpectrumSignalParameters::HrWpanSpectrumSignalParameters(const HrWpanSpectrumSignalParameters& p)
		: SpectrumSignalParameters( p)
	{
		NS_LOG_FUNCTION(this << &p);
		packetBurst = p.packetBurst->Copy();
	}

	Ptr<SpectrumSignalParameters> HrWpanSpectrumSignalParameters::Copy(void)
	{
		NS_LOG_FUNCTION(this);
		return Create<HrWpanSpectrumSignalParameters>(*this);
	}
}