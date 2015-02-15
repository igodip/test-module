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
 * Authors:
 *  Gary Pei <guangyu.pei@boeing.com>
 *  kwong yin <kwong-sang.yin@boeing.com>
 *  Tom Henderson <thomas.r.henderson@boeing.com>
 *  Sascha Alexander Jopen <jopen@cs.uni-bonn.de>
 *  Erwan Livolant <erwan.livolant@inria.fr>
 */
#include "hr-wpan-mac.h"
#include "hr-wpan-csmaca.h"
#include "hr-wpan-mac-header.h"
#include "hr-wpan-mac-trailer.h"
#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/uinteger.h>
#include <ns3/node.h>
#include <ns3/packet.h>
#include <ns3/random-variable-stream.h>
#include <ns3/double.h>

#undef NS_LOG_APPEND_CONTEXT
#define NS_LOG_APPEND_CONTEXT                                   \
  std::clog << "[address " << m_shortAddress << "] ";

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HrWpanMac");

NS_OBJECT_ENSURE_REGISTERED (HrWpanMac);

const uint32_t HrWpanMac::aMinMPDUOverhead = 9; // Table 85

TypeId
HrWpanMac::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HrWpanMac")
    .SetParent<Object> ()
    .AddConstructor<HrWpanMac> ()
    .AddAttribute ("PanId", "16-bit identifier of the associated PAN",
                   UintegerValue (),
                   MakeUintegerAccessor (&HrWpanMac::m_macPanId),
                   MakeUintegerChecker<uint16_t> ())
    .AddTraceSource ("MacTxEnqueue",
                     "Trace source indicating a packet has been "
                     "enqueued in the transaction queue",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macTxEnqueueTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacTxDequeue",
                     "Trace source indicating a packet has was "
                     "dequeued from the transaction queue",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macTxDequeueTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacTx",
                     "Trace source indicating a packet has "
                     "arrived for transmission by this device",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macTxTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacTxOk",
                     "Trace source indicating a packet has been "
                     "successfully sent",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macTxOkTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacTxDrop",
                     "Trace source indicating a packet has been "
                     "dropped during transmission",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macTxDropTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacPromiscRx",
                     "A packet has been received by this device, "
                     "has been passed up from the physical layer "
                     "and is being forwarded up the local protocol stack.  "
                     "This is a promiscuous trace,",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macPromiscRxTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacRx",
                     "A packet has been received by this device, "
                     "has been passed up from the physical layer "
                     "and is being forwarded up the local protocol stack.  "
                     "This is a non-promiscuous trace,",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macRxTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacRxDrop",
                     "Trace source indicating a packet was received, "
                     "but dropped before being forwarded up the stack",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macRxDropTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("Sniffer",
                     "Trace source simulating a non-promiscuous "
                     "packet sniffer attached to the device",
                     MakeTraceSourceAccessor (&HrWpanMac::m_snifferTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("PromiscSniffer",
                     "Trace source simulating a promiscuous "
                     "packet sniffer attached to the device",
                     MakeTraceSourceAccessor (&HrWpanMac::m_promiscSnifferTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MacState",
                     "The state of Wpan Mac",
                     MakeTraceSourceAccessor (&HrWpanMac::m_macStateLogger),
                     "ns3::HrWpanMac::StateTracedCallback")
    .AddTraceSource ("MacSentPkt",
                     "Trace source reporting some information about "
                     "the sent packet",
                     MakeTraceSourceAccessor (&HrWpanMac::m_sentPktTrace),
                     "ns3::HrWpanMac::SentTracedCallback")
  ;
  return tid;
}

HrWpanMac::HrWpanMac ()
{

  // First set the state to a known value, call ChangeMacState to fire trace source.
  m_hrWpanMacState = MAC_IDLE;
  ChangeMacState (MAC_IDLE);

  m_macRxOnWhenIdle = true;
  m_macPanId = 0;
  m_associationStatus = ASSOCIATED;
  m_selfExt = Mac64Address::Allocate ();
  m_macPromiscuousMode = false;
  m_macMaxFrameRetries = 3;
  m_retransmission = 0;
  m_numCsmacaRetry = 0;
  m_txPkt = 0;

  Ptr<UniformRandomVariable> uniformVar = CreateObject<UniformRandomVariable> ();
  uniformVar->SetAttribute ("Min", DoubleValue (0.0));
  uniformVar->SetAttribute ("Max", DoubleValue (255.0));
  m_macDsn = SequenceNumber8 (uniformVar->GetValue ());
  m_devAddrId = HrWpanDevId ("00");
}

HrWpanMac::~HrWpanMac ()
{
}

void
HrWpanMac::DoInitialize ()
{
  if (m_macRxOnWhenIdle)
    {
      m_phy->PlmeSetTRXStateRequest (IEEE_802_15_4_PHY_RX_ON);
    }
  else
    {
      m_phy->PlmeSetTRXStateRequest (IEEE_802_15_4_PHY_TRX_OFF);
    }

  Object::DoInitialize ();
}

void
HrWpanMac::DoDispose ()
{
  if (m_csmaCa != 0)
    {
      m_csmaCa->Dispose ();
      m_csmaCa = 0;
    }
  m_txPkt = 0;
  for (uint32_t i = 0; i < m_txQueue.size (); i++)
    {
      m_txQueue[i]->txQPkt = 0;
      delete m_txQueue[i];
    }
  m_txQueue.clear ();
  m_phy = 0;
  m_mcpsDataIndicationCallback = MakeNullCallback< void, MacAsyncDataIndicationParams, Ptr<Packet> > ();
  m_mcpsDataConfirmCallback = MakeNullCallback< void, MacAsyncDataConfirmationParams > ();

  Object::DoDispose ();
}

bool
HrWpanMac::GetRxOnWhenIdle ()
{
  return m_macRxOnWhenIdle;
}

void
HrWpanMac::SetRxOnWhenIdle (bool rxOnWhenIdle)
{
  NS_LOG_FUNCTION (this << rxOnWhenIdle);
  m_macRxOnWhenIdle = rxOnWhenIdle;

  if (m_hrWpanMacState == MAC_IDLE)
    {
      if (m_macRxOnWhenIdle)
        {
          m_phy->PlmeSetTRXStateRequest (IEEE_802_15_4_PHY_RX_ON);
        }
      else
        {
          m_phy->PlmeSetTRXStateRequest (IEEE_802_15_4_PHY_TRX_OFF);
        }
    }
}

void
HrWpanMac::SetDeviceId (HrWpanDevId address)
{
  //NS_LOG_FUNCTION (this << address);
  m_devAddrId = address;
}

void
HrWpanMac::SetExtendedAddress (Mac64Address address)
{
  //NS_LOG_FUNCTION (this << address);
  m_selfExt = address;
}


HrWpanDevId
HrWpanMac::GetDeviceId () const
{
  NS_LOG_FUNCTION (this);
  return m_devAddrId;
}

Mac64Address
HrWpanMac::GetExtendedAddress () const
{
  NS_LOG_FUNCTION (this);
  return m_selfExt;
}
void
HrWpanMac::MacAsyncDataRequest (MacAsyncDataRequestParams params, Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);


}

void
HrWpanMac::CheckQueue ()
{
  NS_LOG_FUNCTION (this);
  
}

void
HrWpanMac::SetCsmaCa (Ptr<HrWpanCsmaCa> csmaCa)
{
  m_csmaCa = csmaCa;
}

void
HrWpanMac::SetPhy (Ptr<HrWpanPhy> phy)
{
  m_phy = phy;
}

Ptr<HrWpanPhy>
HrWpanMac::GetPhy (void)
{
  return m_phy;
}

void
HrWpanMac::SetMacAsyncIndicationCallback (MacAsyncIndicationCallback c)
{
  m_mcpsDataIndicationCallback = c;
}

void
HrWpanMac::SetMacAsyncConfirmationCallback (MacAsyncConfirmationCallback c)
{
  m_mcpsDataConfirmCallback = c;
}

void
HrWpanMac::PdDataIndication (uint32_t psduLength, Ptr<Packet> p, uint8_t lqi)
{
  NS_ASSERT (m_hrWpanMacState == MAC_IDLE || m_hrWpanMacState == MAC_ACK_PENDING || m_hrWpanMacState == MAC_CSMA);

  NS_LOG_FUNCTION (this << psduLength << p << lqi);

}

void
HrWpanMac::SendAck (uint8_t seqno)
{
  NS_LOG_FUNCTION (this << static_cast<uint32_t> (seqno));

  NS_ASSERT (m_hrWpanMacState == MAC_IDLE);

}

void
HrWpanMac::RemoveFirstTxQElement ()
{
  TxQueueElement *txQElement = m_txQueue.front ();
  Ptr<const Packet> p = txQElement->txQPkt;
  m_numCsmacaRetry += m_csmaCa->GetNB () + 1;

  Ptr<Packet> pkt = p->Copy ();
  HrWpanMacHeader hdr;
  pkt->RemoveHeader (hdr);
  if (hdr.getDstAddress () != HrWpanDevId ("ff"))
    {
      m_sentPktTrace (p, m_retransmission + 1, m_numCsmacaRetry);
    }

  txQElement->txQPkt = 0;
  delete txQElement;
  m_txQueue.pop_front ();
  m_txPkt = 0;
  m_retransmission = 0;
  m_numCsmacaRetry = 0;
  m_macTxDequeueTrace (p);
}

void
HrWpanMac::AckWaitTimeout (void)
{
  NS_LOG_FUNCTION (this);

  // TODO: If we are a PAN coordinator and this was an indirect transmission,
  //       we will not initiate a retransmission. Instead we wait for the data
  //       being extracted after a new data request command.
  if (!PrepareRetransmission ())
    {
      SetHrWpanMacState (MAC_IDLE);
    }
  else
    {
      SetHrWpanMacState (MAC_CSMA);
    }
}

bool
HrWpanMac::PrepareRetransmission (void)
{
  NS_LOG_FUNCTION (this);

  
}

void
HrWpanMac::PdDataConfirm (HrWpanPhyEnumeration status)
{
  NS_ASSERT (m_hrWpanMacState == MAC_SENDING);

  NS_LOG_FUNCTION (this << status << m_txQueue.size ());

  
}

void
HrWpanMac::PlmeCcaConfirm (HrWpanPhyEnumeration status)
{
  NS_LOG_FUNCTION (this << status);
  // Direct this call through the csmaCa object
  m_csmaCa->PlmeCcaConfirm (status);
}

void
HrWpanMac::PlmeEdConfirm (HrWpanPhyEnumeration status, uint8_t energyLevel)
{
  NS_LOG_FUNCTION (this << status << energyLevel);

}

void
HrWpanMac::PlmeGetAttributeConfirm (HrWpanPhyEnumeration status,
                                    HrWpanPibAttributeIdentifier id,
                                    HrWpanPhyPibAttributes* attribute)
{
  NS_LOG_FUNCTION (this << status << id << attribute);
}

void
HrWpanMac::PlmeSetTRXStateConfirm (HrWpanPhyEnumeration status)
{
  NS_LOG_FUNCTION (this << status);

  if (m_hrWpanMacState == MAC_SENDING && (status == IEEE_802_15_4_PHY_TX_ON || status == IEEE_802_15_4_PHY_SUCCESS))
    {
      NS_ASSERT (m_txPkt);

      // Start sending if we are in state SENDING and the PHY transmitter was enabled.
      m_promiscSnifferTrace (m_txPkt);
      m_snifferTrace (m_txPkt);
      m_macTxTrace (m_txPkt);
      m_phy->PdDataRequest (m_txPkt->GetSize (), m_txPkt);
    }
  else if (m_hrWpanMacState == MAC_CSMA && (status == IEEE_802_15_4_PHY_RX_ON || status == IEEE_802_15_4_PHY_SUCCESS))
    {
      // Start the CSMA algorithm as soon as the receiver is enabled.
      m_csmaCa->Start ();
    }
  else if (m_hrWpanMacState == MAC_IDLE)
    {
      NS_ASSERT (status == IEEE_802_15_4_PHY_RX_ON || status == IEEE_802_15_4_PHY_SUCCESS || status == IEEE_802_15_4_PHY_TRX_OFF);
      // Do nothing special when going idle.
    }
  else if (m_hrWpanMacState == MAC_ACK_PENDING)
    {
      NS_ASSERT (status == IEEE_802_15_4_PHY_RX_ON || status == IEEE_802_15_4_PHY_SUCCESS);
    }
  else
    {
      // TODO: What to do when we receive an error?
      // If we want to transmit a packet, but switching the transceiver on results
      // in an error, we have to recover somehow (and start sending again).
      NS_FATAL_ERROR ("Error changing transceiver state");
    }
}

void
HrWpanMac::PlmeSetAttributeConfirm (HrWpanPhyEnumeration status,
                                    HrWpanPibAttributeIdentifier id)
{
  NS_LOG_FUNCTION (this << status << id);
}

void
HrWpanMac::SetHrWpanMacState (HrWpanMacState macState)
{
  NS_LOG_FUNCTION (this << "mac state = " << macState);

  
}

HrWpanAssociationStatus
HrWpanMac::GetAssociationStatus (void) const
{
  return m_associationStatus;
}

void
HrWpanMac::SetAssociationStatus (HrWpanAssociationStatus status)
{
  m_associationStatus = status;
}

uint16_t
HrWpanMac::GetPanId (void) const
{
  return m_macPanId;
}

void
HrWpanMac::SetPanId (uint16_t panId)
{
  m_macPanId = panId;
}

void
HrWpanMac::ChangeMacState (HrWpanMacState newState)
{
  NS_LOG_LOGIC (this << " change lrwpan mac state from "
                     << m_hrWpanMacState << " to "
                     << newState);
  m_macStateLogger (m_hrWpanMacState, newState);
  m_hrWpanMacState = newState;
}

uint64_t
HrWpanMac::GetMacAckWaitDuration (void) const
{
  return m_csmaCa->GetUnitBackoffPeriod () + m_phy->aTurnaroundTime + m_phy->GetPhySHRDuration ()
         + ceil (6 * m_phy->GetPhySymbolsPerOctet ());
}

uint8_t
HrWpanMac::GetMacMaxFrameRetries (void) const
{
  return m_macMaxFrameRetries;
}

void
HrWpanMac::SetMacMaxFrameRetries (uint8_t retries)
{
  m_macMaxFrameRetries = retries;
}

} // namespace ns3
