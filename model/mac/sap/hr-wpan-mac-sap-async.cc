
#include "hr-wpan-mac-sap-async.h"
#include <ns3/log.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-net-device.h>

namespace ns3
{
	namespace HrWpan
	{

		void MacSapUserAsync::Confirm(const MacSapConfirmParamsAsync & confirmParams)
		{
			
		}

		void MacSapUserAsync::Indication(const MacSapIndicationParamsAsync & indicationParams)
		{

		}

		MacSapUserAsync::MacSapUserAsync(HrWpanNetDevice * netDevice) :
			MacSapUser(netDevice)
		{

		}
		
		MacSapProviderAsync::MacSapProviderAsync(HrWpanMac * mac) :
			MacSapProvider(mac)
		{


		}
		
		void MacSapProviderAsync::Request(const MacSapRequestParamsAsync & requestParams)
		{
			//requestParams.
		}

		void MacSapProviderAsync::Response(const MacSapResponseParamsAsync & responseParams)
		{

		}



	} //namespace HrWpan

} // namespace ns3