/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 The Boeing Company
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
 *  Author: kwong yin <kwong-sang.yin@boeing.com>
 */

/*
 * the following classes implements the 802.15.3c Mac Header
 * There are 7 types of 802.15.3c Mac Headers Frames, and they have these fields
 *
 *    Headers Frames  : Fields
 *    -------------------------------------------------------------------------------------------
 *    Beacon          : 
 *	  Immediate Ack	  : FrameType,DestId,SrcId
 *	  Delayed Ack	  : FrameType,DestId,SrcId
 *    Command		  : All but StreamIndex
 *    Data            : All
 *    LLC			  : 
 *	  Sync			  :
 *
 *    + - The Address fields in Beacon frame is made up of the Source PAN Id and address only and size
 *        is  4 or 8 octets whereas the other frames may contain the Destination PAN Id and address as
 *        well. (see specs).
 *    ++ - These fields are optional and of variable size
 */

#ifndef HR_WPAN_MAC_HEADER_H
#define HR_WPAN_MAC_HEADER_H

#include <ns3/header.h>
#include <ns3/hr-wpan-dev-id.h>


namespace ns3 {


	/**
	 * \ingroup hr-wpan
	 * Represent the Mac Header with the Frame Control and Sequence Number fields
	 */
	class HrWpanMacHeader : public Header
	{

	public:

		/**
		 * The possible Frame Types, see IEEE 802.15.3c-2009, Table 39
		 */
		enum HrWpanFrameType
		{
			HRWPAN_FRAME_BEACON = 0,        //!< HRWPAN_MAC_BEACON
			HRWPAN_FRAME_IMM_ACK = 1,          //!< HRWPAN_MAC_DATA
			HRWPAN_FRAME_DEL_ACK = 2,    //!< HRWPAN_MAC_ACKNOWLEDGMENT
			HRWPAN_FRAME_COMMAND = 3,       //!< HRWPAN_MAC_COMMAND
			HRWPAN_FRAME_DATA = 4,		//!< HRWPAN_MAC_DATA_FRAME
			HRWPAN_FRAME_LLC = 5,       //!< HRWPAN_MAC_LLC
			HRWPAN_FRAME_SYNC = 6,		//!< HRWPAN_MAC_SYNC
			HRWPAN_MAC_RESERVED           //!< HRWPAN_MAC_RESERVED
		};

		/**
		*  The possible values of SEC bit, see IEEE 802.15.3, 7.2.1.3
		*/
		enum HrWpanSecBit
		{
			HRWPAN_FRAME_NO_PROT = 0,
			HRWPAN_FRAME_PROT = 1
		};

		/**
		 * The possibile ack policies, see IEEE 802.15.3c, 7.2.1.4 Table 40
		 */
		enum HrWpanAckPolicy
		{
			HRWPAN_POLICY_NOACK = 0x0,  
			HRWPAN_POLICY_IMMACK = 0x1,
			HRWPAN_POLICY_DACK = 0x2,
			HRWPAN_POLICY_DACK_REQ = 0x3,
			HRWPAN_POLICY_IMPACK = 0x5,
			HRWPAN_POLICY_BLKACK = 0x9
		};

		enum HrWpanRetry {
			HRWPAN_RETRY_NO = 0,
			HRWPAN_RETRY_YES = 1
		};

		/**
		 * The addressing mode types, see IEEE 802.15.4-2006, Table 80.
		 */
		enum KeyIdModeType
		{
			IMPLICIT = 0,
			NOKEYSOURCE = 1,
			SHORTKEYSOURCE = 2,
			LONGKEYSOURCE = 3
		};

		HrWpanMacHeader(void);

		/**
		 * Constructor
		 * \param wpanMacType the header MAC type
		 * \param seqNum the sequence number
		 */
		HrWpanMacHeader(enum HrWpanFrameType wpanMacType,      // Data, ACK, Control MAC Header must have
			uint8_t seqNum);                     // frame control and sequence number.
		// Beacon MAC Header must have frame control,
		// sequence number, source PAN Id, source address.

		~HrWpanMacHeader(void);

		/**
		 * Get the header type
		 * \return the header type
		 */
		enum HrWpanFrameType GetType(void) const;
		/**
		 * Get the Frame control field
		 * \return the Frame control field
		 */
		uint16_t GetFrameControl(void) const;

		/**
		 * Check if Security Enabled bit of Frame Control is enabled
		 * \return true if Security Enabled bit is enabled
		 */
		bool IsSecEnable(void) const;

		/**
		 * Get the Reserved bits of Frame control field
		 * \return the Reserved bits
		 */
		uint8_t GetFrmCtrlRes(void) const;

		/**
		 * Get the Protocol Version of Frame control field
		 * \return the Frame Version bits
		 */
		uint8_t GetProtocolVer(void) const;


		/**
		 * Get the frame Sequence number
		 * \return the sequence number
		 */
		uint8_t GetSeqNum(void) const;

		//void get

		/**
		 * Returns true if the header is a beacon
		 * \return true if the header is a beacon
		 */
		bool IsBeacon(void) const;
		/**
		 * Returns true if the header is a data
		 * \return true if the header is a data
		 */
		bool IsData(void) const;
		/**
		 * Returns true if the header is an immediate ack
		 * \return true if the header is an immediate ack
		 */
		bool IsImmediateAck(void) const;
		/**
		 * Returns true if the header is a command
		 * \return true if the header is a command
		 */
		bool IsCommand(void) const;
		/**
		*	Returns true if the header is a delayed ack
		* \return true if the header is a delayed ack
		*/
		bool IsDelayedAck(void) const;

		/**
		 * Set the Frame Control field "Frame Type" bits
		 * \param HrWpanMacType the frame type
		 */
		void SetType(enum HrWpanFrameType wpanFrameType);

		/**
		 * Set the whole Frame Control field
		 * \param frameControl the Frame Control field
		 */
		void SetFrameControl(uint16_t frameControl);

		/**
		 * Set the Frame Control field "Security Enabled" bit to true
		 */
		void SetSecEnable(void);

		/**
		 * Set the Frame Control field "Security Enabled" bit to false
		 */
		void SetSecDisable(void);

		/**
		 * Set the Frame Control field "Frame Pending" bit to true
		 */
		void SetMoreData(void);

		/**
		 * Set the Frame Control field "Frame Pending" bit to false
		 */
		void SetNoMoreData(void);
		/**
		* Set the Ack Policy type
		* \param ackPolicy Ack Policy
		*/
		void SetAckPolicyType(enum HrWpanAckPolicy ackPolicy);
		/**
		*	Get the Ack Policy type
		*
		*/
		enum HrWpanAckPolicy GetAckPolicyType(void) const;

		/**
		 * Set the Frame Control field "Reserved" bits
		 * \param res reserved bits
		 */
		void SetFrmCtrlRes(uint8_t res);
		/**
		 * Set the Protcol version
		 * \param ver frame version
		 */
		void SetProtocolVer(uint8_t ver);
		/**
		* Set the Frame Retry bit to true
		*/
		void SetRetry(void);
		/**
		* Set the Frame Retry bit to false
		*/
		void SetNoRetry(void);
		/**
		* getPiconetId
		* \return piconetId
		*/
		uint8_t getPicoNetId(void) const;
		/**
		* setPiconetId
		* \return piconetId
		*/
		void setPicoNetId(uint8_t piconetId);

		

		/**
		 * \brief Get the type ID.
		 * \return the object TypeId
		 */
		static TypeId GetTypeId(void);
		virtual TypeId GetInstanceTypeId(void) const;

		void Print(std::ostream &os) const;
		uint32_t GetSerializedSize(void) const;
		void Serialize(Buffer::Iterator start) const;
		uint32_t Deserialize(Buffer::Iterator start);


	private:
		/* Frame Control 2 Octets */
		/* Frame Control field - see 7.2.1 */
		uint8_t m_fctrlPtclVrs;               //!< Frame Control field Bit 1-2    = 0 standard protocol
		uint8_t m_fctrlFrameType;             //!< Frame Control field Bit 3-5	
		uint8_t m_fctrlSEC;		              //!< Frame Control field Bit 6
		uint8_t m_fctrlAckPolicy;             //!< Frame Control field Bit 7-8
		uint8_t m_fctrlRetry;			      //!< Frame Control field Bit 9       = 0 - no Retry , 1 - Retry
		uint8_t m_fctrlMoreData;              //!< Frame Control field Bit 10	   = 0 - no more frame in CTA - 1 more frame in CTA
		uint8_t m_fctrlImpAckReq;			  //!< Frame Control field Bit 11	   = 
		uint8_t m_fctrlImpAckNack;			  //!< Frame Control field Bit 12
		uint8_t m_fctrlCTARelinquish;		  //!< Frame Control field Bit 13	   = 1 - CTA Relinquish
		uint8_t m_fctrlBlk_ACK;				  //!< Frame Control field Bit 14
		uint8_t m_fctrlReserved;			  //!< Frame Control field Bit 15

		/* Piconet */
		uint8_t m_picoNetID;			  //!< Piconet ID (1 Octet)

		/* Addressing fields */
		HrWpanDevId m_addrDstId;              //!< Dst id (1 Octet)
		HrWpanDevId m_addrSrcId;			  //!< Src id (1 Octet);

		/* Fragmentation Control*/
		uint16_t m_fragControlMSDUnumber;	//!< Fragmentation control MSDU number Bit 0-8
		uint8_t m_fragControlFragNumber;	//!< Fragmentation control Fragment Number Bit 9-15
		uint8_t m_fragControlLastFragNumber;//!< Fragmentation control Last Fragment number Bit 16-22
		uint8_t m_fragControlReserved;		//!< Fragmentation control Reserved	Bit 23

		/* Stream Index*/
		uint8_t m_StreamIndex;			  //!< Stream index(1 Octet)

	}; //HrWpanMacHeader

}; // namespace ns-3

#endif /* HR_WPAN_MAC_HEADER_H */
