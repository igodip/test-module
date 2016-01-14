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

#ifndef HR_WPAN_CHANNEL_H
#define HR_WPAN_CHANNEL_H

#include <ns3/single-model-spectrum-channel.h>

namespace ns3
{
	namespace HrWpan
	{
		class HrWpanChannell : public SingleModelSpectrumChannel
		{

		public:
			static TypeId GetTypeId(void);
			virtual void StartTx(Ptr<SpectrumSignalParameters> txParams);
		protected:

		private:

		};
	} // namespace HrWpan

} // namespace ns3

#endif //HR_WPAN_CHANNEL_H
