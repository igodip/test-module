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
 * Author: Igor Di Paolo <igor.di.paolo@gmail.com>
 */
#include "hr-wpan-mac-header.h"
#include <ns3/address-utils.h>

namespace ns3 {

	NS_OBJECT_ENSURE_REGISTERED(HrWpanMacHeader);



	HrWpanMacHeader::HrWpanMacHeader()
	{
		SetType(HRWPAN_FRAME_DATA);   // Assume Data frame
		SetSecDisable();              // Assume there is No Aux Sec but
		SetNoMoreData();               // No Frame Pending
		SetAckPolicyType(HRWPAN_POLICY_NOACK);// No Ack Frame will be expected from recepient
		SetFrmCtrlRes(0);             // Initialize the 3 reserved bits to 0
		SetProtocolVer(0);               //Indicates an IEEE 802.15.4 frame
	}


	HrWpanMacHeader::HrWpanMacHeader(enum HrWpanFrameType wpanMacType,
		uint8_t seqNum)
	{
		SetType(wpanMacType);
		//SetSeqNum(seqNum);
		SetSecDisable();              // Assume there is No Aux Sec but
		SetNoMoreData();               // No Frame Pending
		SetAckPolicyType(HRWPAN_POLICY_NOACK);// No Ack Frame will be expected from recepient
		SetFrmCtrlRes(0);             // Initialize the 3 reserved bits to 0
		SetProtocolVer(0);               //Indicates an IEEE 802.15.4 frame
	}


	HrWpanMacHeader::~HrWpanMacHeader()
	{
	}


	enum HrWpanMacHeader::HrWpanFrameType
		HrWpanMacHeader::GetType(void) const
	{
		switch (m_fctrlFrameType)
		{
		case HRWPAN_FRAME_BEACON:
			return HRWPAN_FRAME_BEACON;
		case HRWPAN_FRAME_IMM_ACK:
			return HRWPAN_FRAME_IMM_ACK;
		case HRWPAN_FRAME_DEL_ACK:
			return HRWPAN_FRAME_DEL_ACK;
		case HRWPAN_FRAME_COMMAND:
			return HRWPAN_FRAME_COMMAND;
		case HRWPAN_FRAME_DATA:
			return HRWPAN_FRAME_DATA;
		case HRWPAN_FRAME_LLC:
			return HRWPAN_FRAME_LLC;
		case HRWPAN_FRAME_SYNC:
			return HRWPAN_FRAME_SYNC;
		default:
			return HRWPAN_MAC_RESERVED;
		}
	}



	uint16_t
		HrWpanMacHeader::GetFrameControl(void) const
	{
		uint16_t val = 0;

		val = m_fctrlPtclVrs & (0x07);						// Bit 0-2
		val |= (m_fctrlFrameType << 3) & (0x07 << 3);		// Bit 3-5
		val |= (m_fctrlSEC << 6) & (0x01 << 6);				// Bit 6
		val |= (m_fctrlAckPolicy << 7) & (0x03 << 7);		// Bit 7-8
		val |= (m_fctrlRetry << 9) & (0x01 << 9);			// Bit 9
		val |= (m_fctrlMoreData << 10) & (0x01 << 10);      // Bit 10
		val |= (m_fctrlImpAckReq << 11) & (0x01 << 11);		// Bit 11
		val |= (m_fctrlImpAckNack << 12) & (0x03 << 12);	// Bit 12
		val |= (m_fctrlCTARelinquish << 13) & (0x03 << 13);	// Bit 13
		val |= (m_fctrlBlk_ACK << 14) & (0x01 << 14);		// Bit 14
		val |= (m_fctrlReserved << 15) & (0x01 << 15);		// Bit 15
		return val;

	}

	bool
		HrWpanMacHeader::IsSecEnable(void) const
	{
		return (m_fctrlSEC == HRWPAN_FRAME_PROT);
	}

	uint8_t
		HrWpanMacHeader::GetFrmCtrlRes(void) const
	{
		return (m_fctrlReserved);
	}

	uint8_t
		HrWpanMacHeader::GetProtocolVer(void) const
	{
		return m_fctrlPtclVrs;
	}

	void HrWpanMacHeader::SetAckPolicyType(enum HrWpanAckPolicy ackPolicy){
		m_fctrlAckPolicy = ackPolicy & (0x3); //Bit 0-1
		m_fctrlImpAckReq = (ackPolicy >> 2) & (0x1); //Bit 2
		m_fctrlBlk_ACK = (ackPolicy >> 3) & 0x1; // Bit 3
	}

	enum HrWpanMacHeader::HrWpanAckPolicy HrWpanMacHeader::GetAckPolicyType(void) const {

		switch (m_fctrlAckPolicy)
		{
		case 0x0:
			return HRWPAN_POLICY_NOACK;
			break;

		case 0x1:
			
			if (m_fctrlImpAckReq == 1) {
				return HRWPAN_POLICY_IMPACK;
			}

			if (m_fctrlBlk_ACK == 1){
				return HRWPAN_POLICY_BLKACK;
			}

			return HRWPAN_POLICY_IMMACK;
			break;
		case 0x2:
			
			return HRWPAN_POLICY_DACK;
			break;
		case 0x3:

			return HRWPAN_POLICY_DACK_REQ;
			break;


		}


		

	}


	bool
		HrWpanMacHeader::IsBeacon(void) const
	{
		return(m_fctrlFrameType == HRWPAN_FRAME_BEACON);
	}



	bool
		HrWpanMacHeader::IsData(void) const
	{
		return(m_fctrlFrameType == HRWPAN_FRAME_DATA);
	}





	bool
		HrWpanMacHeader::IsImmediateAck(void) const
	{
		//TODO: How to do this? :D
		return(true);
	}



	bool
		HrWpanMacHeader::IsCommand(void) const
	{
		return(m_fctrlFrameType == HRWPAN_FRAME_COMMAND);
	}



	void
		HrWpanMacHeader::SetType(enum HrWpanFrameType frameType)
	{
		m_fctrlFrameType = frameType;
	}


	void
		HrWpanMacHeader::SetFrameControl(uint16_t frameControl)
	{
		m_fctrlPtclVrs = (frameControl)& (0x07);				//Bit 0-2
		m_fctrlFrameType = (frameControl >> 3) & (0x07);        //Bit 3-5
		m_fctrlSEC = (frameControl >> 6) & (0x01);				//Bit 6
		m_fctrlAckPolicy = (frameControl >> 7) & (0x03);        //Bit 7-8
		m_fctrlRetry = (frameControl >> 9) & (0x01);			//Bit 9
		m_fctrlMoreData = (frameControl >> 10) & (0x01);        //Bit 10
		m_fctrlImpAckReq = (frameControl >> 11) & (0x01);		//Bit 11
		m_fctrlImpAckNack = (frameControl >> 12) & (0x01);      //Bit 12
		m_fctrlCTARelinquish = (frameControl >> 13) & (0x01);   //Bit 13
		m_fctrlBlk_ACK = (frameControl >> 14) & (0x01);			//Bit 14
		m_fctrlReserved = (frameControl >> 15) & (0x01);		//Bit 15
	}


	void
		HrWpanMacHeader::SetSecEnable(void)
	{
		m_fctrlSEC = 1;
	}


	void
		HrWpanMacHeader::SetSecDisable(void)
	{
		m_fctrlSEC = 0;
	}


	void
		HrWpanMacHeader::SetMoreData(void)
	{
		m_fctrlMoreData = 1;
	}


	void
		HrWpanMacHeader::SetNoMoreData(void)
	{
		m_fctrlMoreData = 0;
	}

	void
		HrWpanMacHeader::SetRetry(void)
	{
		m_fctrlRetry = 1;
	}

	void
		HrWpanMacHeader::SetNoRetry(void)
	{
		m_fctrlRetry = 0;
	}


	void
		HrWpanMacHeader::SetFrmCtrlRes(uint8_t res)
	{
		m_fctrlReserved = res;
	}

	TypeId
		HrWpanMacHeader::GetTypeId(void)
	{
		static TypeId tid = TypeId("ns3::HrWpanMacHeader")
			.SetParent<Header>()
			.AddConstructor<HrWpanMacHeader>();
		return tid;
	}

	TypeId
		HrWpanMacHeader::GetInstanceTypeId(void) const
	{
		return GetTypeId();
	}

	void
		HrWpanMacHeader::Print(std::ostream &os) const
	{

		//TODO


	}

	uint32_t
		HrWpanMacHeader::GetSerializedSize(void) const
	{
		/*
		 * Each mac header will have
		 * Frame Control      : 2 octet
		 * PNID				  : 2 Octet
		 * DestId			  : 1 Octet
		 * SrcId			  : 1 Octet
		 * FragmatationControl:	3 Octet
		 * Stream index		  : 1 octet
		 */

		uint32_t size = 10;

		return size;
	}


	void
		HrWpanMacHeader::Serialize(Buffer::Iterator start) const
	{
		Buffer::Iterator i = start;

		//Writing first 2 bytes
		i.WriteHtolsbU16(GetFrameControl());

		//i.WriteU8(GetPN)
		i.WriteU8(GetSeqNum());

		switch (m_fctrlDstAddrMode)
		{
		case NOADDR:
			break;
		case SHORTADDR:
			i.WriteHtolsbU16(GetDstPanId());
			WriteTo(i, m_addrShortDstAddr);
			break;
		case EXTADDR:
			i.WriteHtolsbU16(GetDstPanId());
			WriteTo(i, m_addrExtDstAddr);
			break;
		}

		switch (m_fctrlSrcAddrMode)
		{
		case NOADDR:
			break;
		case SHORTADDR:
			if (!IsPanIdComp())
			{
				i.WriteHtolsbU16(GetSrcPanId());
			}
			WriteTo(i, m_addrShortSrcAddr);
			break;
		case EXTADDR:
			if (!IsPanIdComp())
			{
				i.WriteHtolsbU16(GetSrcPanId());
			}
			WriteTo(i, m_addrExtSrcAddr);
			break;
		}

		if (IsSecEnable())
		{
			i.WriteU8(GetSecControl());
			i.WriteHtolsbU32(GetFrmCounter());

			switch (m_secctrlKeyIdMode)
			{
			case IMPLICIT:
				break;
			case NOKEYSOURCE:
				i.WriteU8(GetKeyIdIndex());
				break;
			case SHORTKEYSOURCE:
				i.WriteHtolsbU32(GetKeyIdSrc32());
				i.WriteU8(GetKeyIdIndex());
				break;
			case LONGKEYSOURCE:
				i.WriteHtolsbU64(GetKeyIdSrc64());
				i.WriteU8(GetKeyIdIndex());
				break;
			}
		}
	}


	uint32_t
		HrWpanMacHeader::Deserialize(Buffer::Iterator start)
	{

		Buffer::Iterator i = start;
		uint16_t frameControl = i.ReadLsbtohU16();
		SetFrameControl(frameControl);

		SetSeqNum(i.ReadU8());
		switch (m_fctrlDstAddrMode)
		{
		case NOADDR:
			break;
		case SHORTADDR:
			m_addrDstPanId = i.ReadLsbtohU16();
			ReadFrom(i, m_addrShortDstAddr);
			break;
		case EXTADDR:
			m_addrDstPanId = i.ReadLsbtohU16();
			ReadFrom(i, m_addrExtDstAddr);
			break;
		}

		switch (m_fctrlSrcAddrMode)
		{
		case NOADDR:
			break;
		case SHORTADDR:
			if (!IsPanIdComp())
			{
				m_addrSrcPanId = i.ReadLsbtohU16();
			}
			else
			{
				if (m_fctrlDstAddrMode > 0)
				{
					m_addrSrcPanId = m_addrDstPanId;
				}
			}
			ReadFrom(i, m_addrShortSrcAddr);
			break;
		case EXTADDR:
			if (!IsPanIdComp())
			{
				m_addrSrcPanId = i.ReadLsbtohU16();
			}
			else
			{
				if (m_fctrlDstAddrMode > 0)
				{
					m_addrSrcPanId = m_addrDstPanId;
				}
			}
			ReadFrom(i, m_addrExtSrcAddr);
			break;
		}

		if (IsSecEnable())
		{
			SetSecControl(i.ReadU8());
			SetFrmCounter(i.ReadLsbtohU32());

			switch (m_secctrlKeyIdMode)
			{
			case IMPLICIT:
				break;
			case NOKEYSOURCE:
				SetKeyId(i.ReadU8());
				break;
			case SHORTKEYSOURCE:
				SetKeyId(i.ReadLsbtohU32(), i.ReadU8());
				break;
			case LONGKEYSOURCE:
				SetKeyId(i.ReadLsbtohU64(), i.ReadU8());
				break;
			}
		}
		return i.GetDistanceFrom(start);
	}

	// ----------------------------------------------------------------------------------------------------------


} //namespace ns3


