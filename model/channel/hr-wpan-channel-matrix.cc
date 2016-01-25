/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2016 KTH
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
*	Mihret Getye Sidelel <mihretgetye@gmail.com>
*/

//#include "hr-wpan-antenna-array-response.h"

#include <ns3/spectrum-channel.h>
#include <ns3/spectrum-phy.h>
#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/assert.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/antenna-model.h>
#include <ns3/propagation-delay-model.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/spectrum-propagation-loss-model.h>
#include <ns3/net-device.h>
#include <ns3/node.h>
#include <ns3/hr-wpan-topology-aggregator.h>
#include <ns3/hr-wpan-sector-antenna.h>
#include <ns3/hr-wpan-net-device.h>
#include <ns3/double.h>
#include <ns3/hr-wpan-channel-matrix.h>
#include <complex>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("HrWpan::ChannelMatrix");

	namespace HrWpan
	{

                ChannelMatrix & ChannelMatrix::getInstance()
		{
			static ChannelMatrix channelMatrix;

			return channelMatrix;
		}

                ChannelMatrix::ChannelMatrix()
		{
			NS_LOG_FUNCTION(this);

			m_noAntennaElementsPerTx = 64;
                        m_noAntennaElementsPerRx = 16;
		}


		TypeId ChannelMatrix::GetTypeId()
		{
			static TypeId tid = TypeId("ChannelMatrix")
				.SetParent<Object>()
                                .AddConstructor<ChannelMatrix>();
			return tid;
		}
		
                std::vector<std::vector<std::complex<double> > > ChannelMatrix::GetTranspose(std::vector<std::complex<double> > antennaResponse)

                        {
                                std::vector<std::vector<std::complex<double> > > arrayTranspose;
                                for(unsigned i=0; i<antennaResponse.size(); ++i){
                                        arrayTranspose[1][i] = antennaResponse[i];
                                }
                                return arrayTranspose;
                        }

                void ChannelMatrix::GenerateChannelMatrix(Ptr<TopologyAggregator> topologyAggregator)
		{		
                        std::list<Ptr<Line> > nodeContainerLines = topologyAggregator->getContainer();
                        std::vector<Ptr<Node> > senders;
                        std::vector<Ptr<Node> > receivers;
                        for(std::list<Ptr<Line> >::iterator it = nodeContainerLines.begin(); it!=nodeContainerLines.end(); it++){
                             Ptr<Link> link = DynamicCast<Link>(*it);
                             senders.push_back(link->GetReceiver());
                             receivers.push_back(link->GetSender());                         
                        }
                        double a_out = 1/30; double b_out = 5.2; double a_los = 1/67.1;
                        double alpha_NLoS = 72.0; double beta_NLoS = 2.92; double sigma_NLoS = 8.7;
			double alpha_LoS = 61.4; double beta_LoS = 2.0; double sigma_LoS = 5.8;
			std::vector<std::vector<double> > distances;
                        std::vector<std::vector<double> > p_outs;
                        std::vector<std::vector<double> > p_LoSs;
                        std::vector<std::vector<double> > p_NLoSs;
                        std::vector<std::vector<double> > linkStates;
                        std::vector<std::vector<double> > pathLossDBs;
                        std::vector<std::vector<double> > gk_olds(senders.size(), std::vector<double>(receivers.size(),-10000.0));
                        std::vector<std::vector<double> > strongestPath(senders.size(), std::vector<double>(receivers.size(),0.0));
                        std::vector<std::vector<double> > strongestPathThetaTx(senders.size(), std::vector<double>(receivers.size(),0.0));
                        std::vector<std::vector<double> > strongestPathThetaRx(senders.size(), std::vector<double>(receivers.size(),0.0));
                        std::vector<std::vector<std::complex<double> > > channelMatrix(senders.size(), std::vector<std::complex<double> >(receivers.size(), 0.0));
                        std::vector<std::vector<double> > gks;
                        distances.resize(senders.size());
                        p_outs.resize(senders.size());
                        p_LoSs.resize(senders.size());	
                        p_NLoSs.resize(senders.size());
                        linkStates.resize(senders.size());
                        pathLossDBs.resize(senders.size());
                        gks.resize(senders.size());			
			for(unsigned i=0; i<senders.size(); ++i){
                                distances[i].resize(receivers.size());
                                p_outs[i].resize(receivers.size());
                                p_LoSs[i].resize(receivers.size());
                                p_NLoSs[i].resize(receivers.size());
                                linkStates[i].resize(receivers.size());
                                pathLossDBs[i].resize(receivers.size());
                                gks[i].resize(receivers.size());
                        }
                        
                        for(unsigned j=0; j<senders.size(); j++){
                                for(unsigned k=0; k<receivers.size(); k++){
                                        Ptr<MobilityModel> senderMobility = senders.at(j)->GetObject<MobilityModel> ();
                                        Ptr<MobilityModel> receiverMobility = receivers.at(k)->GetObject<MobilityModel> ();
                                        distances[j][k] = senderMobility->GetDistanceFrom(receiverMobility);
                                        p_outs[j][k] = std::max(0.0, 1-exp((a_out*distances[j][k]*-1)+b_out));
                                        p_LoSs[j][k] = (1 - p_outs[j][k] )*exp(a_los*distances[j][k]*-1);
                                        p_NLoSs[j][k] = 1 - p_outs[j][k] - p_LoSs[j][k];
                                        Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
					x->SetAttribute ("Min", DoubleValue (0));
					x->SetAttribute ("Max", DoubleValue (1));
                                        linkStates[j][k] = x->GetValue ();
                                        if(linkStates[j][k]<p_outs[j][k]){
						linkStates[j][k] = 0.0;
					}else if(linkStates[j][k]<p_LoSs[j][k]){
						linkStates[j][k] = 1.0;
					}else if(linkStates[j][k] !=0.0 && linkStates[j][k] !=1.0){
						linkStates[j][k]= 2.0;
					}
                                        if(linkStates[j][k] == 0.0){
                                                pathLossDBs[j][k] = 200.0;
                                        }else if(linkStates[j][k] == 1.0){
                                                Ptr<NormalRandomVariable> x = CreateObject<NormalRandomVariable> ();
						x->SetAttribute ("Mean", DoubleValue (0.0));
						x->SetAttribute ("Variance", DoubleValue (sigma_LoS));
						double normrnd = x->GetValue ();
						pathLossDBs[j][k] = alpha_LoS + 10*beta_LoS*log10(distances[j][k]) + normrnd;
                                        }else if(linkStates[j][k] == 2.0){
                                               Ptr<NormalRandomVariable> x = CreateObject<NormalRandomVariable> ();
						x->SetAttribute ("Mean", DoubleValue (0.0));
						x->SetAttribute ("Variance", DoubleValue (sigma_NLoS));
						double normrnd = x->GetValue ();
						pathLossDBs[j][k] = alpha_NLoS +10*beta_NLoS*log10(distances[j][k]) + normrnd; 

                                        }
                                } 
                        }				
			
                        int mpc = 2; 
                        double gamma = 1/mpc;
                        for(int l=1; l<=mpc; l++){
                                Ptr<UniformRandomVariable> y = CreateObject<UniformRandomVariable> ();
			        y->SetAttribute ("Min", DoubleValue (0));
			        y->SetAttribute ("Max", DoubleValue (2*M_PI));
			        std::vector<std::vector<double> > thetaTxs(senders.size(), std::vector<double>(receivers.size(),y->GetValue ()));

                                Ptr<UniformRandomVariable> z = CreateObject<UniformRandomVariable> ();	
        		        z->SetAttribute ("Min", DoubleValue (0));
			        z->SetAttribute ("Max", DoubleValue (2*M_PI));
                                std::vector<std::vector<double> > thetaRxs(senders.size(), std::vector<double>(receivers.size(),z->GetValue ()));
                                for(unsigned i=0; i<senders.size(); i++){
                                        for(unsigned k=0; k<receivers.size(); k++){
                                                Ptr<NormalRandomVariable> x = CreateObject<NormalRandomVariable> ();
				                x->SetAttribute ("Mean", DoubleValue (0.0));
                                                                                           
				                x->SetAttribute ("Variance", DoubleValue (gamma*(pow(10, -0.1*pathLossDBs[i][k]))));
				                gks[i][k] = x->GetValue ();
                                                std::complex<double> mycomplexTx(0, M_PI*sin(thetaTxs[i][k]));
                                                std::complex<double> mycomplexRx(0, M_PI*sin(thetaRxs[i][k]));
                                                std::vector<std::complex<double> > antennaResponseTx;
                                                std::vector<std::complex<double> > antennaResponseRx;
                                                for(unsigned j=0; j<senders.size(); j++){
                                                        const double minusOne = -1.0;
                                                        double oneOverNTx = (double)(1/senders.size()); 
                                                        antennaResponseTx.push_back(oneOverNTx*exp(minusOne*(double)(j)*mycomplexTx));     
                                                }
                                                for(unsigned j=0; j<receivers.size(); j++){
                                                        double oneOverNRx = (double)(1/receivers.size()); 
                                                        antennaResponseRx.push_back(oneOverNRx*exp((double)(j)*mycomplexRx));
                                                }
                                                channelMatrix[i][k] = channelMatrix[i][k]+(double)(gks[i][k])*antennaResponseRx.at(k)*antennaResponseTx.at(i);
                                                if(gks[i][k] > gk_olds[i][k]){

                                                        strongestPath[i][k] = l; 
                                                        strongestPathThetaTx[i][k] = thetaTxs[i][k];
                                                        strongestPathThetaRx[i][k] = thetaRxs[i][k];
                                                }
                                        }
                                }
                                gk_olds = gks; 
                        }
                }
}
}

