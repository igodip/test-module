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
 * Author:
 *  kwong yin <kwong-sang.yin@boeing.com>
 *  Sascha Alexander Jopen <jopen@cs.uni-bonn.de>
 */

#include "hr-wpan-csmaca.h"
#include <ns3/random-variable-stream.h>
#include <ns3/simulator.h>
#include <ns3/log.h>
#include <algorithm>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HrWpanCsmaCa");

NS_OBJECT_ENSURE_REGISTERED (HrWpanCsmaCa);

TypeId
HrWpanCsmaCa::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HrWpanCsmaCa")
    .SetParent<Object> ()
    .AddConstructor<HrWpanCsmaCa> ()
  ;
  return tid;
}

HrWpanCsmaCa::HrWpanCsmaCa ()
{
  // TODO-- make these into ns-3 attributes

  m_isSlotted = false;
  m_NB = 0;
  m_CW = 2;
  m_BLE = false;
  m_macMinBE = 3;
  m_macMaxBE = 5;
  m_macMaxCSMABackoffs = 4;
  m_aUnitBackoffPeriod = 20; //20 symbols
  m_random = CreateObject<UniformRandomVariable> ();
  m_BE = m_macMinBE;
  m_ccaRequestRunning = false;
}

HrWpanCsmaCa::~HrWpanCsmaCa ()
{
  m_mac = 0;
}

void
HrWpanCsmaCa::DoDispose ()
{
  m_hrWpanMacStateCallback = MakeNullCallback< void, HrWpanMacState> ();
  Cancel ();
  m_mac = 0;
}

void
HrWpanCsmaCa::SetMac (Ptr<HrWpanMac> mac)
{
  m_mac = mac;
}

Ptr<HrWpanMac>
HrWpanCsmaCa::GetMac (void) const
{
  return m_mac;
}

void
HrWpanCsmaCa::SetSlottedCsmaCa (void)
{
  NS_LOG_FUNCTION (this);
  m_isSlotted = true;
}

void
HrWpanCsmaCa::SetUnSlottedCsmaCa (void)
{
  NS_LOG_FUNCTION (this);
  m_isSlotted = false;
}

bool
HrWpanCsmaCa::IsSlottedCsmaCa (void) const
{
  NS_LOG_FUNCTION (this);
  return (m_isSlotted);
}

bool
HrWpanCsmaCa::IsUnSlottedCsmaCa (void) const
{
  NS_LOG_FUNCTION (this);
  return (!m_isSlotted);
}

void
HrWpanCsmaCa::SetMacMinBE (uint8_t macMinBE)
{
  NS_LOG_FUNCTION (this << macMinBE);
  m_macMinBE = macMinBE;
}

uint8_t
HrWpanCsmaCa::GetMacMinBE (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMinBE;
}

void
HrWpanCsmaCa::SetMacMaxBE (uint8_t macMaxBE)
{
  NS_LOG_FUNCTION (this << macMaxBE);
  m_macMinBE = macMaxBE;
}

uint8_t
HrWpanCsmaCa::GetMacMaxBE (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMaxBE;
}

void
HrWpanCsmaCa::SetMacMaxCSMABackoffs (uint8_t macMaxCSMABackoffs)
{
  NS_LOG_FUNCTION (this << macMaxCSMABackoffs);
  m_macMaxCSMABackoffs = macMaxCSMABackoffs;
}

uint8_t
HrWpanCsmaCa::GetMacMaxCSMABackoffs (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMaxCSMABackoffs;
}

void
HrWpanCsmaCa::SetUnitBackoffPeriod (uint64_t unitBackoffPeriod)
{
  NS_LOG_FUNCTION (this << unitBackoffPeriod);
  m_aUnitBackoffPeriod = unitBackoffPeriod;
}

uint64_t
HrWpanCsmaCa::GetUnitBackoffPeriod (void) const
{
  NS_LOG_FUNCTION (this);
  return m_aUnitBackoffPeriod;
}

Time
HrWpanCsmaCa::GetTimeToNextSlot (void) const
{
  NS_LOG_FUNCTION (this);

  // TODO: Calculate the offset to the next slot.

  return Seconds (0);

}
void
HrWpanCsmaCa::Start ()

{
  NS_LOG_FUNCTION (this);
  m_NB = 0;
  if (IsSlottedCsmaCa ())
    {
      m_CW = 2;
      if (m_BLE)
        {
          m_BE = std::min (static_cast<uint8_t> (2), m_macMinBE);
        }
      else
        {
          m_BE = m_macMinBE;
        }
      //TODO: for slotted, locate backoff period boundary. i.e. delay to the next slot boundary
      Time backoffBoundary = GetTimeToNextSlot ();
      m_randomBackoffEvent = Simulator::Schedule (backoffBoundary, &HrWpanCsmaCa::RandomBackoffDelay, this);
    }
  else
    {
      m_BE = m_macMinBE;
      m_randomBackoffEvent = Simulator::ScheduleNow (&HrWpanCsmaCa::RandomBackoffDelay, this);
    }
  /*
  *  TODO: If using Backoff.cc (will need to modify Backoff::GetBackoffTime)
  *        Backoff.m_minSlots = 0;
  *        Backoff.m_ceiling = m_BE;
  *        Backoff.ResetBackoffTime(); //m_NB is same as m_numBackoffRetries in Backoff.h
  *        Backoff.m_maxRetries = macMaxCSMABackoffs;
  *        Backoff.m_slotTime = m_backoffPeriod;
  */
}

void
HrWpanCsmaCa::Cancel ()
{

}

/*
 * Delay for backoff period in the range 0 to 2^BE -1 units
 * TODO: If using Backoff.cc (Backoff::GetBackoffTime) will need to be slightly modified
 */
void
HrWpanCsmaCa::RandomBackoffDelay ()
{
  NS_LOG_FUNCTION (this);


}

// TODO : Determine if transmission can be completed before end of CAP for the slotted csmaca
//        If not delay to the next CAP
void
HrWpanCsmaCa::CanProceed ()
{
  NS_LOG_FUNCTION (this);

}

void
HrWpanCsmaCa::RequestCCA ()
{
  NS_LOG_FUNCTION (this);

}

/*
 * This function is called when the phy calls back after completing a PlmeCcaRequest
 */
void
HrWpanCsmaCa::PlmeCcaConfirm (HrWpanPhyEnumeration status)
{
  NS_LOG_FUNCTION (this << status);

  
}

void
HrWpanCsmaCa::SetHrWpanMacStateCallback (HrWpanMacStateCallback c)
{
  NS_LOG_FUNCTION (this);
  
}

int64_t
HrWpanCsmaCa::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this);
  
  return 1;
}

uint8_t
HrWpanCsmaCa::GetNB (void)
{
  return m_NB;
}

} //namespace ns3
