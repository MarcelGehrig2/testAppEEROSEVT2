#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/hal/HAL.hpp>

#include "Print.hpp"
#include "RosBlockSubscriber_SensorMsgs_LaserScan.hpp"
#include "RosBlockPublisher_SensorMsgs_LaserScan.hpp"

using namespace eeros::control;

class MyControlSystem {		
public:
// 	MyControlSystem(double dt);
	MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler);

	
	// Define blocks
	Print<double> printDouble0;
	Print<bool> printBool0;
	
	typedef eeros::math::Matrix< 5, 1, double >		TRangesOutput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesOutput;
	RosBlockSubscriber_SensorMsgs_LaserScan<TRangesOutput, TIntensitiesOutput>	laserScanIn;
	typedef eeros::math::Matrix< 5, 1, double >		TRangesInput;
	typedef eeros::math::Matrix< 5, 1, double >		TIntensitiesInput;
	RosBlockPublisher_SensorMsgs_LaserScan<TRangesInput, TIntensitiesInput>		laserScanOut;

	//HAL
	PeripheralInput<double>		analogIn0;
	PeripheralInput<bool>		digitalIn0;
	PeripheralOutput<double>	analogOut0;
	PeripheralOutput<bool>		digitalOut0;
			
//	protected:
	double dt;
	ros::NodeHandle& rosNodeHandler;
	bool realtime;
	eeros::control::TimeDomain timedomain;
};

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
