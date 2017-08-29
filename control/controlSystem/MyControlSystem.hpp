#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/hal/HAL.hpp>

#include <eeros/control/ROS/RosBlockPublisherDouble.hpp>
#include <eeros/control/Sum.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/I.hpp>
#include <eeros/control/D.hpp>
#include <eeros/control/Saturation.hpp>

#include "Print.hpp"
#include "MyStep.hpp"
#include "MyFilter.hpp"
#include "Discret.hpp"
#include "RosBlockSubscriber_SensorMsgs_LaserScan.hpp"
#include "RosBlockPublisher_SensorMsgs_LaserScan.hpp"

using namespace eeros::control;

class MyControlSystem {		
public:
	MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler);

	
	// RosBlocks
	typedef eeros::math::Matrix< 5, 1, double >		TRangesOutput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesOutput;
	RosBlockSubscriber_SensorMsgs_LaserScan<TRangesOutput, TIntensitiesOutput>	laserScanIn;
	typedef eeros::math::Matrix< 5, 1, double >		TRangesInput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesInput;
	RosBlockPublisher_SensorMsgs_LaserScan<TRangesInput, TIntensitiesInput>		laserScanOut;
	
	// HAL 
	PeripheralInput<double>		analogIn;
	PeripheralInput<double>		motorPositionIn;
	PeripheralOutput<double>	effortOut;
	
	Discret		discreterEncoder;
	
	// Define blocks
	Print<double> printDouble0;
	Print<double> printDouble1;
	Print<double> printDouble2;
	
	// Controler blocks
	Constant<double>		motorPositionInFake;
	D<double> 			posToVel;
	MyFilter			lowPassFilter;
	Sum<2, double>			diffVel;
	Gain<double>			pwGain;
	Gain<double>			iwGain;
	I<double>			iwIntegrator;
	Sum<2, double>			iSum;
	Saturation<double>		iSaturation;
	Gain<double>			kmGain;
	
	//Publisher for debuging
	RosBlockPublisherDouble		motorPositionInPublisher;
	RosBlockPublisherDouble		analogInPublisher;
	RosBlockPublisherDouble		iwGainPublisher;
	RosBlockPublisherDouble		posToVelPublisher;
	RosBlockPublisherDouble		iwIntegratorPublisher;
	RosBlockPublisherDouble		iSumPublisher;
	RosBlockPublisherDouble		kmGainPublisher;
	
//	protected:
	double dt;
	ros::NodeHandle& rosNodeHandler;
	bool realtime;
	eeros::control::TimeDomain timedomain;
};

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
