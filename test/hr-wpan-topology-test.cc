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
* Author: Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#include <ns3/test.h>
#include <ns3/log.h>
#include <ns3/position-allocator.h>
#include <ns3/double.h>

#include <iostream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("HrWpanTopologyTestCase");

/** 

**/

class HrWpanTopologyTestCase : public TestCase
{
public:
	HrWpanTopologyTestCase();
	virtual ~HrWpanTopologyTestCase();

private:
	virtual void DoRun(void);
};

HrWpanTopologyTestCase::HrWpanTopologyTestCase()
	: TestCase("Test the topology creation")
{

}

HrWpanTopologyTestCase::~HrWpanTopologyTestCase()
{

}

void HrWpanTopologyTestCase::DoRun(void)
{

	Ptr<UniformRandomVariable> uniform_x = CreateObject<UniformRandomVariable>();
	Ptr<UniformRandomVariable> uniform_y = CreateObject<UniformRandomVariable>();

	uniform_x->SetAttribute("Min", DoubleValue(0));
	uniform_x->SetAttribute("Max", DoubleValue(10));
	uniform_y->SetAttribute("Min", DoubleValue(0));
	uniform_y->SetAttribute("Max", DoubleValue(10));

	uniform_x->SetStream(10);
	uniform_y->SetStream(15);

	RandomRectanglePositionAllocator randomRectanglePositionAllocator;

	randomRectanglePositionAllocator.SetX(uniform_x);
	randomRectanglePositionAllocator.SetY(uniform_y);

	std::cout << randomRectanglePositionAllocator.GetNext() << std::endl;
	std::cout << randomRectanglePositionAllocator.GetNext() << std::endl;
	std::cout << randomRectanglePositionAllocator.GetNext() << std::endl;

}

class HrWpanPlacingObstaclesTestCase : public TestCase
{
public:
	HrWpanPlacingObstaclesTestCase();
	virtual ~HrWpanPlacingObstaclesTestCase();

private:
	virtual void DoRun(void);
};

HrWpanPlacingObstaclesTestCase::HrWpanPlacingObstaclesTestCase() 
	: TestCase("Placing obstacle test")
{

}

HrWpanPlacingObstaclesTestCase::~HrWpanPlacingObstaclesTestCase()
{

}


void HrWpanPlacingObstaclesTestCase::DoRun()
{

}

class HrWpanTopologyTestSuite : public TestSuite
{
public:
	HrWpanTopologyTestSuite();
};



HrWpanTopologyTestSuite::HrWpanTopologyTestSuite()
	: TestSuite("hr-wpan-topology-test", UNIT)
{
	AddTestCase(new HrWpanTopologyTestCase, TestCase::QUICK);
	AddTestCase(new HrWpanPlacingObstaclesTestCase, TestCase::QUICK);
}

static HrWpanTopologyTestSuite hrWpanTopologyTestSuite;

