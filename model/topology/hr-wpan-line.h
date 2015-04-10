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

#ifndef  HR_WPAN_LINE_H
#define HR_WPAN_LINE_H

#include <ns3/vector.h>
#include <ns3/object.h>

namespace ns3
{
	namespace HrWpan
	{
		class Line : public Object
		{
		public:
			Line();
			Line(double start_x, double start_y,
				double end_x, double end_y);
			
			// inherited from Object
			static TypeId GetTypeId(void);
			
			void setStart(const Vector3D & start);
			void setEnd(const Vector3D & end);

			virtual Vector3D getStart();
			virtual Vector3D getEnd() ;

		protected:

			// inherited from Object
			virtual void DoDispose();

			Vector3D m_start;
			Vector3D m_end;
		};
	}
}

#endif