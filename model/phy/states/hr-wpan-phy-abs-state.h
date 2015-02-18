/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
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
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#ifndef HR_WPAN_ABS_STATE_H
#define HR_WPAN_ABS_STATE_H

#include <ns3/object.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/hr-wpan-spectrum-signal-parameters.h>

namespace ns3
{
	class HrWpanPhy;

	/**
	 * \class	HrWpanAbsState
	 *
	 * \brief	A hr wpan abstract state.
	 *
	 * \author	Igor
	 * \date	17/02/2015
	 */

	class HrWpanPhyAbsState : public Object
	{
	public:

		/**
		 * \fn	HrWpanAbsState::HrWpanAbsState(Ptr < HrWpanPhy > hrWpanPhy)
		 *
		 * \brief	Constructor.
		 *
		 *
		 * \param	hrWpanPhy	The hr wpan phy.
		 */

		HrWpanPhyAbsState(Ptr < HrWpanPhy >  hrWpanPhy):
			m_hrWpanPhy(hrWpanPhy)
		{}

		/**
		 * \fn	virtual void HrWpanAbsState::StartRx(Ptr<SpectrumSignalParameters> params);
		 *
		 * \brief	Starts a receive.
		 *
		 *
		 * \param	params	Options for controlling the operation.
		 */

		virtual void StartRx(Ptr<SpectrumSignalParameters> params);

		/**
		 * \fn	virtual void HrWpanAbsState::EndRx(Ptr<SpectrumSignalParameters> params);
		 *
		 * \brief	Ends a receive.
		 *
		 * \param	params	Options for controlling the operation.
		 */

		virtual void EndRx(Ptr<SpectrumSignalParameters> params);

		/**
		 * \fn	virtual void HrWpanAbsState::StartTx(Ptr<SpectrumSignalParameters> params);
		 *
		 * \brief	Starts a transmit.
		 *
		 *
		 * \param	params	Options for controlling the operation.
		 */

		virtual void StartTx(Ptr<HrWpanSpectrumSignalParameters> params) ;

		/**
		 * \fn	virtual void HrWpanAbsState::EndTx(Ptr<SpectrumSignalParameters> params);
		 *
		 * \brief	Ends a transmit.
		 *
		 * \param	params	Options for controlling the operation.
		 */

		virtual void EndTx(Ptr<HrWpanSpectrumSignalParameters> params) ;

	protected:
		Ptr<HrWpanPhy> m_hrWpanPhy;
	};
}

#endif