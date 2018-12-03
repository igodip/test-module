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

#ifndef HR_WPAM_PHY_PREAMBLE_H
#define HR_WPAM_PHY_PREAMBLE_H

#include <ns3/chunk.h>

namespace ns3
{
	namespace HrWpan
	{
		class PhyPreamble : public Chunk
		{
			/**
			* \brief Get the type ID.
			* \return the object TypeId
			*/
			static TypeId GetTypeId(void);

			/**
			* \brief Deserialize the object from a buffer iterator
			* \param start the buffer iterator
			* \returns the number of deserialized bytes
			*/
			virtual uint32_t Deserialize(Buffer::Iterator start) = 0;

			/**
			* \brief Print the object contents
			* \param os the output stream
			*/
			virtual void Print(std::ostream &os) const = 0;
		};
	}
}

#endif //HR_WPAM_PHY_PREAMBLE_H