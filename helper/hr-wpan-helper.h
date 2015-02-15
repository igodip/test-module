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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#ifndef HR_WPAN_HELPER_H
#define HR_WPAN_HELPER_H

#include <ns3/ptr.h>
#include <ns3/node-container.h>
#include <ns3/net-device-container.h>
#include <ns3/hr-wpan-phy.h>

namespace ns3 {

	class SpectrumChannel;
	class MobilityModel;

	class HrWpanHelper {
	public:
		/**
		 * \fn	HrWpanHelper::HrWpanHelper(void);
		 *
		 * \brief	Default constructor.
		 *
		 */

		HrWpanHelper(void);

		/**
		 * \fn	HrWpanHelper::HrWpanHelper(bool useMultiModelSpectrumChannel);
		 *
		 * \brief	Constructor.
		 *
		 * \param	useMultiModelSpectrumChannel	true to use multi model spectrum channel.
		 */

		HrWpanHelper(bool useMultiModelSpectrumChannel);

		/**
		 * \fn	virtual HrWpanHelper::~HrWpanHelper(void);
		 *
		 * \brief	Destructor.
		 */

		virtual ~HrWpanHelper(void);

		/**
		 * \fn	Ptr<SpectrumChannel> HrWpanHelper::GetChannel(void);
		 *
		 * \brief	Gets the channel.
		 *
		 * \return	The channel.
		 */

		Ptr<SpectrumChannel> GetChannel(void);

		/**
		 * \fn	void HrWpanHelper::SetChannel(Ptr<SpectrumChannel> channel);
		 *
		 * \brief	Sets a channel.
		 *
		 * \param	channel	The channel.
		 */

		void SetChannel(Ptr<SpectrumChannel> channel);

		/**
		 * \fn	NetDeviceContainer HrWpanHelper::install(NodeContainer c);
		 *
		 * \brief	Installs the given c.
		 *
		 * \param	c	The NodeContainer to process.
		 *
		 * \return	A NetDeviceContainer.
		 */

		NetDeviceContainer install(NodeContainer c);

	private:

		/** \brief	channel to be used for the devices. */
		Ptr<SpectrumChannel> m_channel;

	};

}

#endif