
#include "hr-wpan-mac-sap-async.h"
#include <ns3/log.h>
#include <ns3/hr-wpan-mac.h>
#include <ns3/hr-wpan-net-device.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("HrWpanMacSapAsync");

	namespace HrWpan
	{

		void MacSapUserAsync::Confirm(const MacSapConfirmParams & confirmParams)
		{
			NS_LOG_FUNCTION(this);
		}

		void MacSapUserAsync::Indication(const MacSapIndicationParams & indicationParams)
		{
			NS_LOG_FUNCTION(this);
			
			const MacSapIndicationParamsAsync & paramsAsync = dynamic_cast<const MacSapIndicationParamsAsync &>(indicationParams);
			m_netDevice->Receive(paramsAsync.m_data);

		}

		MacSapUserAsync::MacSapUserAsync(HrWpanNetDevice * netDevice) :
			MacSapUser(netDevice)
		{
			NS_LOG_FUNCTION(this);
		}
		
		MacSapProviderAsync::MacSapProviderAsync(HrWpanMac * mac) :
			MacSapProvider(mac)
		{
			NS_LOG_FUNCTION(this);

		}
		
		void MacSapProviderAsync::Request(const MacSapRequestParams & requestParams)
		{
			NS_LOG_FUNCTION(this);

			const MacSapRequestParamsAsync & paramsAsync = dynamic_cast<const MacSapRequestParamsAsync &>(requestParams);

			HrWpanPhyProvider* provider = m_mac->GetPhyProvider();
			// Add header and trailer
			provider->SendMacPdu(paramsAsync.m_data);

		}

		void MacSapProviderAsync::Response(const MacSapResponseParams & responseParams)
		{
			NS_LOG_FUNCTION(this);


		}



	} //namespace HrWpan

} // namespace ns3