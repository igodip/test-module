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
 * the following classes implements the 802.15.4 Mac Header
 * There are 4 types of 802.15.4 Mac Headers Frames, and they have these fields
 *
 *    Headers Frames  : Fields
 *    -------------------------------------------------------------------------------------------
 *    Beacon          : Frame Control, Sequence Number, Address Fields+, Auxiliary Security Header++.
 *    Data            : Frame Control, Sequence Number, Address Fields++, Auxiliary Security Header++.
 *    Acknowledgment  : Frame Control, Sequence Number.
 *    Command         : Frame Control, Sequence Number, Address Fields++, Auxiliary Security Header++.
 *
 *    + - The Address fields in Beacon frame is made up of the Source PAN Id and address only and size
 *        is  4 or 8 octets whereas the other frames may contain the Destination PAN Id and address as
 *        well. (see specs).
 *    ++ - These fields are optional and of variable size
 */

#ifndef HR_WPAN_MAC_HEADER_H
#define HR_WPAN_MAC_HEADER_H

#include <ns3/header.h>
#include <ns3/mac16-address.h>
#include <ns3/mac64-address.h>


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
		*  The possible value of SEC bit, see IEEE 802.15.3, 7.2.1.3
		*/
		enum HrWpanSecBit
		{
			HRWPAN_FRAME_NO_PROT = 0,
			HRWPAN_FRAME_PROT = 1
		};

		/**
		 *
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
		 * Check if Frame Pending bit of Frame Control is enabled
		 * \return true if Frame Pending bit is enabled
		 */
		bool IsFrmPend(void) const;

		/**
		 * Check if Ack. Request bit of Frame Control is enabled
		 * \return true if Ack. Request bit is enabled
		 */
		bool IsAckReq(void) const;

		/**
		 * Check if PAN ID Compression bit of Frame Control is enabled
		 * \return true if PAN ID Compression bit is enabled
		 */
		bool IsPanIdComp(void) const;

		/**
		 * Get the Reserved bits of Frame control field
		 * \return the Reserved bits
		 */
		uint8_t GetFrmCtrlRes(void) const;

		/**
		 * Get the Frame Version of Frame control field
		 * \return the Frame Version bits
		 */
		uint8_t GetFrameVer(void) const;


		/**
		 * Get the frame Sequence number
		 * \return the sequence number
		 */
		uint8_t GetSeqNum(void) const;

		/**
		 * Get the Destination PAN ID
		 * \return the Destination PAN ID
		 */
		uint16_t GetDstPanId(void) const;
		/**
		 * Get the Destination Extended address
		 * \return the Destination Extended address
		 */
		Mac64Address GetExtDstAddr(void) const;
		/**
		 * Get the Source PAN ID
		 * \return the Source PAN ID
		 */
		uint16_t GetSrcPanId(void) const;
		/**
		 * Get the Source Short address
		 * \return the Source Short address
		 */
		Mac16Address GetShortSrcAddr(void) const;
		/**
		 * Get the Source Extended address
		 * \return the Source Extended address
		 */
		Mac64Address GetExtSrcAddr(void) const;

		/**
		 * Get the Auxiliary Security Header - Security Control Octect
		 * \return the Auxiliary Security Header - Security Control Octect
		 */
		uint8_t GetSecControl(void) const;
		/**
		 * Get the Auxiliary Security Header - Frame Counter Octects
		 * \return the Auxiliary Security Header - Frame Counter Octects
		 */
		uint32_t GetFrmCounter(void) const;

		/**
		 * Get the Auxiliary Security Header - Security Control - Security Level bits
		 * \return the Auxiliary Security Header - Security Control - Security Level bits
		 */
		uint8_t GetSecLevel(void) const;
		/**
		 * Get the Auxiliary Security Header - Security Control - Key Identifier Mode bits
		 * \return the Auxiliary Security Header - Security Control - Key Identifier Mode bits
		 */
		uint8_t GetKeyIdMode(void) const;
		/**
		 * Get the Auxiliary Security Header - Security Control - Reserved bits
		 * \return the Auxiliary Security Header - Security Control - Reserved bits
		 */
		uint8_t GetSecCtrlReserved(void) const;

		/**
		 * Get the Auxiliary Security Header - Key Identifier - Key Source (2 Octects)
		 * \return the Auxiliary Security Header - Key Identifier - Key Source  (2 Octects)
		 */
		uint32_t GetKeyIdSrc32(void) const;
		/**
		 * Get the Auxiliary Security Header - Key Identifier - Key Source (4 Octects)
		 * \return the Auxiliary Security Header - Key Identifier - Key Source  (4 Octects)
		 */
		uint64_t GetKeyIdSrc64(void) const;
		/**
		 * Get the Auxiliary Security Header - Key Identifier - Key Index
		 * \return the Auxiliary Security Header - Key Identifier - Key Index
		 */
		uint8_t GetKeyIdIndex(void) const;

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
		 * Returns true if the header is an ack
		 * \return true if the header is an ack
		 */
		bool IsAcknowledgment(void) const;
		/**
		 * Returns true if the header is a command
		 * \return true if the header is a command
		 */
		bool IsCommand(void) const;

		/**
		 * Set the Frame Control field "Frame Type" bits
		 * \param wpanMacType the frame type
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
		void SetFrmPend(void);

		/**
		 * Set the Frame Control field "Frame Pending" bit to false
		 */
		void SetNoFrmPend(void);

		/**
		 * Set the Frame Control field "Ack. Request" bit to true
		 */
		void SetAckReq(void);

		/**
		 * Set the Frame Control field "Ack. Request" bit to false
		 */
		void SetNoAckReq(void);

		/**
		 * Set the Frame Control field "Reserved" bits
		 * \param res reserved bits
		 */
		void SetFrmCtrlRes(uint8_t res);
		/**
		 * Set the Frame version
		 * \param ver frame version
		 */
		void SetFrameVer(uint8_t ver);

		/**
		 * Set the Sequence number
		 * \param seqNum sequence number
		 */
		void SetSeqNum(uint8_t seqNum);

		/* The Source/Destination Addressing fields are only set if SrcAddrMode/DstAddrMode are set */
		/**
		 * Set Source address fields
		 * \param panId source PAN ID
		 * \param addr source address (16 bit)
		 */
		void SetSrcAddrFields(uint16_t panId, Mac16Address addr);
		/**
		 * Set Source address fields
		 * \param panId source PAN ID
		 * \param addr source address (64 bit)
		 */
		void SetSrcAddrFields(uint16_t panId, Mac64Address addr);
		/**
		 * Set Destination address fields
		 * \param panId destination PAN ID
		 * \param addr destination address (16 bit)
		 */
		void SetDstAddrFields(uint16_t panId, Mac16Address addr);
		/**
		 * Set Destination address fields
		 * \param panId destination PAN ID
		 * \param addr destination address (64 bit)
		 */
		void SetDstAddrFields(uint16_t panId, Mac64Address addr);

		/* Auxiliary Security Header is only set if Sec Enable (SecU) field is set to 1 */
		/**
		 * Set the auxiliary security header "Security Control" octet
		 * \param secLevel the "Security Control" octect
		 */
		void SetSecControl(uint8_t secLevel);
		/**
		 * Set the auxiliary security header "Frame Counter" octet
		 * \param frmCntr the "Frame Counter" octect
		 */
		void SetFrmCounter(uint32_t frmCntr);

		/**
		 * Set the Security Control field "Security Level" bits (3 bits)
		 * \param secLevel the "Security Level" bits
		 */
		void SetSecLevel(uint8_t secLevel);
		/**
		 * Set the Security Control field "Key Identifier Mode" bits (2 bits)
		 * \param keyIdMode the "Key Identifier Mode" bits
		 */
		void SetKeyIdMode(uint8_t keyIdMode);

		/**
		 * Set the Security Control field "Reserved" bits (3 bits)
		 * \param res the "Reserved" bits
		 */
		void SetSecCtrlReserved(uint8_t res);

		/* Variable length will be dependent on Key Id Mode*/
		/**
		 * Set the Key Index
		 * \param keyIndex the Key index
		 */
		void SetKeyId(uint8_t keyIndex);
		/**
		 * Set the Key Index and originator
		 * \param keySrc the originator of a group key
		 * \param keyIndex the Key index
		 */
		void SetKeyId(uint32_t keySrc, uint8_t keyIndex);
		/**
		 * Set the Key Index and originator
		 * \param keySrc the originator of a group key
		 * \param keyIndex the Key index
		 */
		void SetKeyId(uint64_t keySrc, uint8_t keyIndex);

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
		uint8_t m_addrDstId;              //!< Dst id (1 Octet)
		uint8_t m_addrSrcId;			  //!< Src id (1 Octet);

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
