
#include "hr-wpan-mac-sap.h"

#include <ns3/hr-wpan-mac.h>

#include <ns3/log.h>

namespace ns3
{
	namespace HrWpan
	{
		MacSapProvider::MacSapProvider(HrWpanMac* mac) :
			m_mac(mac)
		{

		}

		MacSapUser::MacSapUser(HrWpanNetDevice * netDevice,HrWpanMac * mac) :
			m_netDevice(netDevice), m_mac(mac)
		{

		}
	}
}