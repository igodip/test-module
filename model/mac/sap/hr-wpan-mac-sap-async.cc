
#include "hr-wpan-mac-sap-async.h"

namespace ns3
{
	namespace HrWpan
	{

		MacSapProviderAsync::MacSapProviderAsync(HrWpanMac * mac) :
			MacSapProvider(mac)
		{

		}

		MacSapUserAsync::MacSapUserAsync(HrWpanNetDevice * netDevice) :
			MacSapUser(netDevice)
		{

		}


	} //namespace HrWpan

} // namespace ns3