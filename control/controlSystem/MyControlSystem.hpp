#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/hal/HAL.hpp>

#include <eeros/control/RosBlockPublisherDouble.hpp>
#include <eeros/control/Sum.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/I.hpp>
#include <eeros/control/D.hpp>

#include "Print.hpp"
#include "MyStep.hpp"
#include "RosBlockSubscriber_SensorMsgs_LaserScan.hpp"
#include "RosBlockPublisher_SensorMsgs_LaserScan.hpp"

using namespace eeros::control;

class MyControlSystem {		
public:
// 	MyControlSystem(double dt);
	MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler);

	
	// RosBlocks
	typedef eeros::math::Matrix< 5, 1, double >		TRangesOutput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesOutput;
	RosBlockSubscriber_SensorMsgs_LaserScan<TRangesOutput, TIntensitiesOutput>	laserScanIn;
	typedef eeros::math::Matrix< 5, 1, double >		TRangesInput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesInput;
	RosBlockPublisher_SensorMsgs_LaserScan<TRangesInput, TIntensitiesInput>		laserScanOut;
	
	// HAL 
	PeripheralInput<double>		analogIn0;
	PeripheralInput<double>		motorPositionIn0;
// // 	PeripheralInput<bool>		digitalIn0;
	PeripheralOutput<double>	motorEffortOut0;
// // 	PeripheralOutput<bool>		digitalOut0;
	
	// Define blocks
	Print<double> printDouble0;
	Print<double> printDouble1;
	Print<double> printDouble2;
// 	Print<bool> printBool0;
	
	// Controler blocks
// 	MyStep<double> stepIn0;
// 	MyStep<double> asd;
	D<double> 			posToVel0;
	Sum<2, double>		diffVel0;
	Gain<double>		pwGain0;
	Gain<double>		iwGain0;
	I<double>			iwIntegrator0;
	Sum<2, double>		iwSum0;
	Gain<double>		kmGain0;
	
// 	Sum<1, double>		sum1;
// 	Constant<double>	const1;
	
	
	//Publisher for debuging
	RosBlockPublisherDouble		analogIn0Publisher;
	RosBlockPublisherDouble		posToVel0Publisher;
	RosBlockPublisherDouble		iwIntegrator0Publisher;
	RosBlockPublisherDouble		iwSum0Publisher;
			
//	protected:
	double dt;
	ros::NodeHandle& rosNodeHandler;
	bool realtime;
	eeros::control::TimeDomain timedomain;
};

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
