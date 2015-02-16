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

#ifndef HR_WPAN_PHY_ATTRIBUTES_H
#define HR_WPAN_PHY_ATTRIBUTES_H

namespace ns3 {

	typedef enum
	{

		IEEE_802_15_3_PHY_BUSY = 0x00,
		IEEE_802_15_3_PHY_BUSY_RX = 0x01,
		IEEE_802_15_3_PHY_BUSY_TX = 0x02,
		IEEE_802_15_3_PHY_FORCE_TRX_OFF = 0x03,
		IEEE_802_15_3_PHY_IDLE = 0x04,
		IEEE_802_15_3_PHY_INVALID_PARAMETER = 0x05,
		IEEE_802_15_3_PHY_RX_ON = 0x06,
		IEEE_802_15_3_PHY_SUCCESS = 0x07,
		IEEE_802_15_3_PHY_TRX_OFF = 0x08,
		IEEE_802_15_3_PHY_TX_ON = 0x09,
		IEEE_802_15_3_PHY_UNSUPPORTED_ATTRIBUTE = 0xa,
		IEEE_802_15_3_PHY_READ_ONLY = 0xb,
		IEEE_802_15_3_PHY_UNSPECIFIED = 0xc // all cases not covered by ieee802.15.3

	}HrWpanPhyEnumeration;

	/**
	 * \typedef	enum
	 *
	 * \brief	Defines an alias representing the enum.
	 */

	typedef enum
	{
		IEEE_802_15_3_2_4_GHZ = 0,
		IEEE_802_15_3_MMWAVE  = 1

	} HrWpanPhyPibTypeEnumeration;

	/**
	 * \typedef	enum
	 *
	 * \brief	Defines an alias representing the enum.
	 */

	typedef enum
	{
		IEEE_802_15_3_SC_PHY = 0x1,
		IEEE_802_15_3_HSI_PHY = 0x2,
		IEEE_802_15_3_AV_PHY = 0x4,
		IEEE_802_15_3_OOK_MODE = 0x8,
		IEEE_802_15_3_DAMI_MODE = 0x10,
		IEEE_802_15_3_RESERVED1_MODE = 0x20,
		IEEE_802_15_3_RESERVED2_MODE = 0x40,
		IEEE_802_15_3_RESERVED3_MODE = 0x80
	}HrWpanPhyPibModeEnumeration;

	/**
	 * \typedef	enum
	 *
	 * \brief	Defines an alias representing the enum.
	 */

	typedef enum
	{
		IEEE_802_15_3_CHANNEL_1 = 0x1,
		IEEE_802_15_3_CHANNEL_2 = 0x2,
		IEEE_802_15_3_CHANNEL_3 = 0x3,
		IEEE_802_15_3_CHANNEL_4 = 0x4,
	}HrWpanPhyCurrentChannelEnumeration;

	/**
	 * \typedef	enum
	 *
	 * \brief	Defines an alias representing the enum.
	 */

	typedef enum
	{
		IEEE_802_15_3_REG_ETSI = 0x0, 
		IEEE_802_15_3_REG_FCC = 0x1,
		IEEE_802_15_3_REG_IC = 0x2,
		IEEE_802_15_3_REG_ARIB = 0x3
	}HrWpanPhyCurrentRegDomainEnumeration;

	struct HrWpanPhyPIBAttributes {
		HrWpanPhyCurrentChannelEnumeration channelEnum;


	};


} //namespace ns3

#endif
