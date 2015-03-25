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

#ifndef HR_WPAN_MAC_STAT_HELPER_H
#define HR_WPAN_MAC_STAT_HELPER_H

#include <ns3/packet.h>

namespace ns3
{
	namespace HrWpan
	{
		class MacStatHelper
		{
		public:
			MacStatHelper();

			void reset();

			void attach();

			uint32_t getTx() const;
			uint32_t getRx() const;
			uint32_t getQueueDrop() const;
			uint32_t getQueueIn() const;
			uint32_t getQueueOut() const;

		private:

			void incRx(std::string str, Ptr<const Packet> p);
			void incTx(std::string str, Ptr<const Packet> p);
			void incQueueDrop(std::string str, Ptr<const Packet> p);
			void incQueueIn(std::string str, Ptr<const Packet> p);
			void incQueueOut(std::string str, Ptr<const Packet> p);

			uint32_t m_tx;
			uint32_t m_rx;
			uint32_t m_queueDrop;
			uint32_t m_queueIn;
			uint32_t m_queueOut;

		};

	} //namespace HrWpan

}// namespace ns3

#endif //HR_WPAN_MAC_STAT_HELPER_H