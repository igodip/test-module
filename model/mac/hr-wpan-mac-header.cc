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
 * Author: Igor Di Paolo <igor.di.paolo@gmail.com>
 */

#include "hr-wpan-mac-header.h"
#include <ns3/address-utils.h>
#include <ns3/log.h>

namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanMacHeader");

	namespace HrWpan
	{

		NS_OBJECT_ENSURE_REGISTERED(MacHeader);

		MacHeader::MacHeader()
		{

			NS_LOG_FUNCTION(this);

			SetType(HRWPAN_FRAME_DATA);   // Assume Data frame
			SetSecDisable();              // Assume there is No Aux Sec but
			SetNoMoreData();               // No Frame Pending
			SetAckPolicyType(HRWPAN_POLICY_NOACK);// No Ack Frame will be expected from recepient
			SetFrmCtrlRes(0);             // Initialize the 3 reserved bits to 0
			SetProtocolVer(0);               //Indicates an IEEE 802.15.4 frame
		}


		MacHeader::MacHeader(enum FrameType wpanMacType, uint8_t seqNum)
		{

			NS_LOG_FUNCTION(this);

			SetType(wpanMacType);
			//SetSeqNum(seqNum);
			SetSecDisable();              // Assume there is No Aux Sec but
			SetNoMoreData();               // No Frame Pending
			SetAckPolicyType(HRWPAN_POLICY_NOACK);// No Ack Frame will be expected from recepient
			SetFrmCtrlRes(0);             // Initialize the 3 reserved bits to 0
			SetProtocolVer(0);               //Indicates an IEEE 802.15.4 frame
		}


		MacHeader::~MacHeader()
		{
			NS_LOG_FUNCTION(this);
		}


		enum MacHeader::FrameType
			MacHeader::GetType(void) const
		{

			NS_LOG_FUNCTION(this);

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



		uint16_t MacHeader::GetFrameControl(void) const
		{

			NS_LOG_FUNCTION(this);

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

		bool MacHeader::IsSecEnable(void) const
		{
			NS_LOG_FUNCTION(this);

			return (m_fctrlSEC == HRWPAN_FRAME_PROT);
		}

		uint8_t MacHeader::GetFrmCtrlRes(void) const
		{
			NS_LOG_FUNCTION(this);

			return (m_fctrlReserved);
		}

		uint8_t MacHeader::GetProtocolVer(void) const
		{
			NS_LOG_FUNCTION(this);

			return m_fctrlPtclVrs;
		}

		void MacHeader::SetProtocolVer(uint8_t protVer)
		{
			NS_LOG_FUNCTION(this << protVer);

			m_fctrlPtclVrs = protVer;
		}

		uint16_t MacHeader::getPicoNetId(void) const
		{
			NS_LOG_FUNCTION(this);
			return m_picoNetID;
		}

		void MacHeader::setPicoNetId(uint16_t picoNetId)
		{
			NS_LOG_FUNCTION(this << picoNetId);

			m_picoNetID = picoNetId;
		}

		void MacHeader::SetAckPolicyType(enum AckPolicy ackPolicy)
		{
			NS_LOG_FUNCTION(this << ackPolicy);

			m_fctrlAckPolicy = ackPolicy & (0x3); //Bit 0-1
			m_fctrlImpAckReq = (ackPolicy >> 2) & (0x1); //Bit 2
			m_fctrlBlk_ACK = (ackPolicy >> 3) & 0x1; // Bit 3
		}

		enum AckPolicy MacHeader::GetAckPolicyType(void) const {

			NS_LOG_FUNCTION(this);

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

			default:
				return HRWPAN_POLICY_NOACK;

			}

		}


		bool MacHeader::IsBeacon(void) const
		{
			NS_LOG_FUNCTION(this);

			return(m_fctrlFrameType == HRWPAN_FRAME_BEACON);
		}



		bool MacHeader::IsData(void) const
		{
			NS_LOG_FUNCTION(this);

			return(m_fctrlFrameType == HRWPAN_FRAME_DATA);
		}

		bool MacHeader::IsImmediateAck(void) const
		{
			NS_LOG_FUNCTION(this);



			return(true);
		}

		bool MacHeader::IsCommand(void) const
		{
			NS_LOG_FUNCTION(this);

			return(m_fctrlFrameType == HRWPAN_FRAME_COMMAND);
		}

		void MacHeader::SetType(enum FrameType frameType)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlFrameType = frameType;
		}


		void MacHeader::SetFrameControl(uint16_t frameControl)
		{

			NS_LOG_FUNCTION(this);

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


		void MacHeader::SetSecEnable(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlSEC = 1;
		}


		void MacHeader::SetSecDisable(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlSEC = 0;
		}


		void MacHeader::SetMoreData(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlMoreData = 1;
		}


		void MacHeader::SetNoMoreData(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlMoreData = 0;
		}

		void MacHeader::SetRetry(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlRetry = 1;
		}

		void MacHeader::SetNoRetry(void)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlRetry = 0;
		}


		void MacHeader::SetFrmCtrlRes(uint8_t res)
		{
			NS_LOG_FUNCTION(this);

			m_fctrlReserved = res;
		}

		void MacHeader::setDstAddress(const HrWpan::DevId & wpanDevId)
		{
			NS_LOG_FUNCTION(this);

			m_addrDstId = wpanDevId;
		}

		HrWpan::DevId MacHeader::getDstAddress(void) const
		{
			NS_LOG_FUNCTION(this);

			return m_addrDstId;
		}

		void MacHeader::setSrcAddress(const HrWpan::DevId & wpanDevId)
		{
			NS_LOG_FUNCTION(this);

			m_addrSrcId = wpanDevId;
		}

		HrWpan::DevId MacHeader::getSrcAddress(void) const
		{

			NS_LOG_FUNCTION(this);

			return m_addrSrcId;
		}

		void MacHeader::setStreamIndex(uint8_t streamIndex){

			NS_LOG_FUNCTION(this);

			m_StreamIndex = streamIndex;
		}

		uint8_t MacHeader::getStreamIndex(void) const {

			NS_LOG_FUNCTION(this);

			return m_StreamIndex;
		}

		TypeId MacHeader::GetTypeId(void)
		{
			static TypeId tid = TypeId("ns3::HrWpan::MacHeader")
				.SetParent<Header>()
				.AddConstructor<MacHeader>();
			return tid;
		}

		TypeId MacHeader::GetInstanceTypeId(void) const
		{
			NS_LOG_FUNCTION(this);

			return GetTypeId();
		}

		void MacHeader::setFragmentationControl(uint32_t fragmentationControl)
		{
			NS_LOG_FUNCTION(this);
		}

		uint32_t MacHeader::getFragmentationControl() const {

			NS_LOG_FUNCTION(this);

			uint32_t result = 0;

			result |= m_fragControlMSDUnumber & 0x1FF;
			result |= m_fragControlFragNumber & 0xFE00;
			result |= m_fragControlLastFragNumber & 0x7F0000;
			result |= m_fragControlReserved & 0x800000;

			return result;

		}

		void MacHeader::Print(std::ostream &os) const
		{
			NS_LOG_FUNCTION(this);
			//TODO


		}

		uint32_t MacHeader::GetSerializedSize(void) const
		{
			/*
			* Each mac header will have
			* Frame Control       : 2 octet
			* PNID				  : 2 Octet
			* DestId			  : 2 Octet
			* SrcId			      : 2 Octet
			* FragmatationControl :	3 Octet
			* Stream index		  : 1 octet
			*/

			NS_LOG_FUNCTION(this);

			uint32_t size = 12;

			return size;
		}


		//TODO: Ho qualche forte dubbio su queste funzioni

		void MacHeader::Serialize(Buffer::Iterator start) const
		{

			NS_LOG_FUNCTION(this);

			Buffer::Iterator i = start;

			//Writing first 2 bytes
			i.WriteHtolsbU16(GetFrameControl());

			i.WriteHtolsbU16(getPicoNetId());

			WriteTo(i, getDstAddress());
			WriteTo(i, getSrcAddress());

			//Fragmentation control
			i.WriteU8(0);
			i.WriteU8(0);
			i.WriteU8(0);

			i.WriteU8(getStreamIndex());

		}


		//TODO: Forte dubbio anche qui

		uint32_t MacHeader::Deserialize(Buffer::Iterator start)
		{
			NS_LOG_FUNCTION(this);

			Buffer::Iterator i = start;
			uint16_t frameControl = i.ReadLsbtohU16();
			SetFrameControl(frameControl);

			uint8_t picoNetId = i.ReadLsbtohU16();
			setPicoNetId(picoNetId);

			Address dstAddrId, srcAddrId;

			ReadFrom(i, dstAddrId, 2);
			ReadFrom(i, srcAddrId, 2);

			setDstAddress(DevId::convertFrom(dstAddrId));
			setSrcAddress(DevId::convertFrom(srcAddrId));

			//Fragmentation control
			//TODO
			i.ReadU8();
			i.ReadU8();
			i.ReadU8();
			setFragmentationControl(0);

			uint8_t streamIndex = i.ReadU8();
			setStreamIndex(streamIndex);


			return i.GetDistanceFrom(start);
		}

	}

	// ----------------------------------------------------------------------------------------------------------


} //namespace ns3


