
#ifndef HR_WPAN_MAC_SAP_H
#define HR_WPAN_MAC_SAP_H

#include <ns3/object.h>

namespace ns3
{

	class HrWpanMacSapRequestParams 
	{

	};

	class HrWpanMacSapResponseParams 
	{

	};

	class HrWpanMacSapConfirmParams 
	{

	};

	class HrWpanMacSapIndicationParams 
	{

	};

	class HrWpanMacSapProvider
	{
	public:
		virtual void Confirm(HrWpanMacSapConfirmParams & confirmParams) {};
		virtual void Indication(HrWpanMacSapIndicationParams & indicationParams) {};

	};

	class HrWpanMacSapUser
	{
	public:
		virtual void Request() {};
		virtual void Response() {};
	};


} // namespace ns3

#endif //HR_WPAN_MAC_SAP_H