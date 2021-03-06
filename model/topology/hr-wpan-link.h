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

#ifndef HR_WPAN_LINK_H
#define HR_WPAN_LINK_H

#include "hr-wpan-line.h"
#include <ns3/node.h>
#include <ns3/ptr.h>

namespace ns3
{
	namespace HrWpan
	{
		class Link : public Line
		{
		public:

			Link();
			Link(Ptr<Node> sender, Ptr<Node> receiver);

			// inherited from Object
			static TypeId GetTypeId(void);
			

			void SetSender(Ptr<Node> sender);
			void SetReceiver(Ptr<Node> receiver);

			Ptr<Node> GetSender() const;
			Ptr<Node> GetReceiver() const;

			virtual Vector3D getStart();
			virtual Vector3D getEnd();

		protected:
			virtual void DoDispose();

			Ptr<Node> m_sender;
			Ptr<Node> m_receiver;

		};

	} // namespace HrWpan

} // namespace ns3

#endif // HR_WPAN_LINK_H