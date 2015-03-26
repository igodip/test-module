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
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include "hr-wpan-helper.h"

#include <ns3/single-model-spectrum-channel.h>
#include <ns3/multi-model-spectrum-channel.h>
#include <ns3/hr-wpan-obstacle-propagation-model.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/output-stream-wrapper.h>
#include <ns3/ptr.h>
#include <ns3/log.h>
#include <ns3/config.h>
#include <ns3/double.h>


namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("HrWpanHelper");

	namespace HrWpan {

		HrWpanHelper::HrWpanHelper(Ptr<TopologyAggregator> topologyAggregator) {

			NS_LOG_FUNCTION(this);

			m_channel = CreateObject<SingleModelSpectrumChannel>();
			m_channel->SetAttribute("MaxLossDb", DoubleValue(70));

			Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();
			m_channel->AddPropagationLossModel(lossModel);

			Ptr<ObstaclePropagationLossModel> obstacleModel = CreateObject<ObstaclePropagationLossModel>(topologyAggregator);
			lossModel->SetNext(obstacleModel);

			Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();
			m_channel->SetPropagationDelayModel(delayModel);
		}

		HrWpanHelper::HrWpanHelper(Ptr<TopologyAggregator> topologyAggregator, bool useMultiModelSpectrumChannel)
		{
			NS_LOG_FUNCTION(this);

			if (useMultiModelSpectrumChannel)
			{
				m_channel = CreateObject<MultiModelSpectrumChannel>();
			}
			else
			{
				m_channel = CreateObject<SingleModelSpectrumChannel>();
			}
			Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel>();
			m_channel->AddPropagationLossModel(lossModel);

			Ptr<ObstaclePropagationLossModel> obstacleModel = CreateObject<ObstaclePropagationLossModel>(topologyAggregator);
			lossModel->SetNext(obstacleModel);

			Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();
			m_channel->SetPropagationDelayModel(delayModel);
		}

		HrWpanHelper::~HrWpanHelper(void)
		{
			NS_LOG_FUNCTION(this);
			m_channel->Dispose();
			m_channel = 0;
		}

		Ptr<SpectrumChannel> HrWpanHelper::GetChannel(void)
		{
			NS_LOG_FUNCTION(this);
			return m_channel;
		}

		void HrWpanHelper::SetChannel(Ptr<SpectrumChannel> spectrumChannel)
		{
			NS_LOG_FUNCTION(this << spectrumChannel);
			m_channel = spectrumChannel;
		}

		NetDeviceContainer HrWpanHelper::Install(NodeContainer c)
		{

			NS_LOG_FUNCTION(this);

			NetDeviceContainer devices;

			for (NodeContainer::Iterator i = c.Begin(); i != c.End(); i++)
			{

				Ptr<Node> node = *i;

				Ptr<HrWpanNetDevice> netDevice = CreateObject<HrWpanNetDevice>();

				node->AddDevice(netDevice);
				netDevice->SetNode(node);

				netDevice->SetChannel(m_channel);
				devices.Add(netDevice);

			}

			return devices;

		}

		void HrWpanHelper::EnablePcapInternal(std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename)
		{
			//
			// All of the Pcap enable functions vector through here including the ones
			// that are wandering through all of devices on perhaps all of the nodes in
			// the system.  We can only deal with devices of type CsmaNetDevice.
			//
			Ptr<HrWpanNetDevice> device = nd->GetObject<HrWpanNetDevice>();
			if (device == 0)
			{
				NS_LOG_INFO("HrWpanHelper::EnablePcapInternal(): Device " << device << " not of type ns3::HrWpanNetDevice");
				return;
			}

			PcapHelper pcapHelper;

			std::string filename;
			if (explicitFilename)
			{
				filename = prefix;
			}
			else
			{
				filename = pcapHelper.GetFilenameFromDevice(prefix, device);
			}

			Ptr<HrWpanMac > mac = device->GetMac();

			Ptr<PcapFileWrapper> file = pcapHelper.CreateFile(filename, std::ios::out,
				PcapHelper::DLT_EN10MB);
			if (promiscuous)
			{
				pcapHelper.HookDefaultSink<HrWpanMac>(mac, "PromiscSniffer", file);
			}
			else
			{
				pcapHelper.HookDefaultSink<HrWpanMac>(mac, "Sniffer", file);
			}
		}

		void HrWpanHelper::EnableAsciiInternal(	Ptr<OutputStreamWrapper> stream,std::string prefix,	Ptr<NetDevice> nd,bool explicitFilename)
		{
			//
			// All of the ascii enable functions vector through here including the ones
			// that are wandering through all of devices on perhaps all of the nodes in
			// the system.  We can only deal with devices of type CsmaNetDevice.
			//
			Ptr<HrWpanNetDevice> device = nd->GetObject<HrWpanNetDevice>();
			if (device == 0)
			{
				NS_LOG_INFO("HrWpanHelper::EnableAsciiInternal(): Device " << device << " not of type ns3::HrWpanNetDevice");
				return;
			}

			//
			// Our default trace sinks are going to use packet printing, so we have to 
			// make sure that is turned on.
			//
			Packet::EnablePrinting();

			//
			// If we are not provided an OutputStreamWrapper, we are expected to create 
			// one using the usual trace filename conventions and do a Hook*WithoutContext
			// since there will be one file per context and therefore the context would
			// be redundant.
			//
			if (stream == 0)
			{
				//
				// Set up an output stream object to deal with private ofstream copy 
				// constructor and lifetime issues.  Let the helper decide the actual
				// name of the file given the prefix.
				//
				AsciiTraceHelper asciiTraceHelper;

				std::string filename;
				if (explicitFilename)
				{
					filename = prefix;
				}
				else
				{
					filename = asciiTraceHelper.GetFilenameFromDevice(prefix, device);
				}

				Ptr<OutputStreamWrapper> theStream = asciiTraceHelper.CreateFileStream(filename);

				//
				// The MacRx trace source provides our "r" event.
				//
				asciiTraceHelper.HookDefaultReceiveSinkWithoutContext<HrWpanNetDevice>(device, "MacRx", theStream);

				//
				// The "+", '-', and 'd' events are driven by trace sources actually in the
				// transmit queue.
				//
				//Ptr<Queue> queue = device->GetQueue();
				//asciiTraceHelper.HookDefaultEnqueueSinkWithoutContext<Queue>(queue, "Enqueue", theStream);
				//asciiTraceHelper.HookDefaultDropSinkWithoutContext<Queue>(queue, "Drop", theStream);
				//asciiTraceHelper.HookDefaultDequeueSinkWithoutContext<Queue>(queue, "Dequeue", theStream);

				return;
			}

			//
			// If we are provided an OutputStreamWrapper, we are expected to use it, and
			// to providd a context.  We are free to come up with our own context if we
			// want, and use the AsciiTraceHelper Hook*WithContext functions, but for 
			// compatibility and simplicity, we just use Config::Connect and let it deal
			// with the context.
			//
			// Note that we are going to use the default trace sinks provided by the 
			// ascii trace helper.  There is actually no AsciiTraceHelper in sight here,
			// but the default trace sinks are actually publicly available static 
			// functions that are always there waiting for just such a case.
			//
			uint32_t nodeid = nd->GetNode()->GetId();
			uint32_t deviceid = nd->GetIfIndex();
			std::ostringstream oss;

			oss << "/NodeList/" << nd->GetNode()->GetId() << "/DeviceList/" << deviceid << "/$ns3::CsmaNetDevice/MacRx";
			Config::Connect(oss.str(), MakeBoundCallback(&AsciiTraceHelper::DefaultReceiveSinkWithContext, stream));

			oss.str("");
			oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CsmaNetDevice/TxQueue/Enqueue";
			Config::Connect(oss.str(), MakeBoundCallback(&AsciiTraceHelper::DefaultEnqueueSinkWithContext, stream));

			oss.str("");
			oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CsmaNetDevice/TxQueue/Dequeue";
			Config::Connect(oss.str(), MakeBoundCallback(&AsciiTraceHelper::DefaultDequeueSinkWithContext, stream));

			oss.str("");
			oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CsmaNetDevice/TxQueue/Drop";
			Config::Connect(oss.str(), MakeBoundCallback(&AsciiTraceHelper::DefaultDropSinkWithContext, stream));
		}


	} // namespace hrWpan

} // namespace ns3
