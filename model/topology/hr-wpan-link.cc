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

#include "hr-wpan-link.h"
#include <ns3/log.h>
#include <ns3/mobility-model.h>

namespace ns3
{
	namespace HrWpan
	{

		Link::Link() :
			m_sender(0), m_receiver(0)
		{

		}


		Link::Link(Ptr<Node> sender, Ptr<Node> receiver) :
			m_sender(sender), m_receiver(receiver)
		{

		}

		TypeId Link::GetTypeId(void)
		{
			TypeId tid = TypeId("HrWpan::Link").
				SetParent<Line>().
				AddConstructor<Link>();
				
			return tid;
		}


		void Link::DoDispose()
		{
			Line::DoDispose();
		}

		void Link::SetSender(Ptr<Node> sender)
		{
			m_sender = sender;
		}

		void Link::SetReceiver(Ptr<Node> receiver)
		{
			m_receiver = receiver;
		}

		Ptr<Node> Link::GetSender() const
		{
			return m_sender;
		}

		Ptr<Node> Link::GetReceiver() const
		{
			return m_receiver;
		}

		Vector3D Link::getStart()
		{
			Ptr<MobilityModel> model = m_sender->GetObject<MobilityModel>();
			return model->GetPosition();
		}

		Vector3D Link::getEnd()
		{
			Ptr<MobilityModel> model = m_sender->GetObject<MobilityModel>();
			return model->GetPosition();
		}

	} // namespace HrWpan

} // namespace ns3
