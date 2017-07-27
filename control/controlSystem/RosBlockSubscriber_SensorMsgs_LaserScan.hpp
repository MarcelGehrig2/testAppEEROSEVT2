#ifndef ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP
#define ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP

// #include <ros/ros.h>
#include <eeros/control/RosBlockSubscriber.hpp>
#include <eeros/core/System.hpp>

#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

typedef sensor_msgs::LaserScan::Type	TRosMsg;
// typedef double							TOutDouble;


class RosBlockSubscriber_SensorMsgs_LaserScan : public RosBlockSubscriber< TRosMsg > {
public:
	RosBlockSubscriber_SensorMsgs_LaserScan(ros::NodeHandle& rosNodeHandler, const std::string& topic, const uint32_t queueSize=1000, const bool callNewest=false) :
// 		rosNodeHandler(rosNodeHandler),
		RosBlockSubscriber< TRosMsg >( rosNodeHandler, topic, queueSize, callNewest )
		{}
		
	void rosCallbackFct(const TRosMsg& msg) {
		// USER DEFINED: 1.) Set timestamp for all outputs
		//               2.) Get the data from the message
		//               3.) Cast the data if necessary
		//               4.) Insert the data into output

		
		// TODO timing from header
		auto time = eeros::System::getTimeNs();
		angle_minOut.getSignal().setTimestamp( time );
		angle_maxOut.getSignal().setTimestamp( time );
		angle_incrementOut.getSignal().setTimestamp( time );
		time_incrementOut.getSignal().setTimestamp( time );
		scan_timeOut.getSignal().setTimestamp( time );
		range_minOut.getSignal().setTimestamp( time );
		range_maxOut.getSignal().setTimestamp( time );
		
		// set value
		angle_minOut.getSignal().setValue(			static_cast< double > ( msg.angle_min ) );
		angle_maxOut.getSignal().setValue(			static_cast< double > ( msg.angle_max ) );
		angle_incrementOut.getSignal().setValue(	static_cast< double > ( msg.angle_increment ) );
		time_incrementOut.getSignal().setValue(		static_cast< double > ( msg.time_increment ) );
		scan_timeOut.getSignal().setValue(			static_cast< double > ( msg.scan_time ) );
		range_minOut.getSignal().setValue(			static_cast< double > ( msg.range_min ) );
		range_maxOut.getSignal().setValue(			static_cast< double > ( msg.range_max ) );
	}

	// USER DEFINED: Add a 'getOut()' function for each output
	Output<double>& getAngle_minOut()			{return angle_minOut; }
	Output<double>& getAngle_maxOut()			{return angle_maxOut; }
	Output<double>& getAngle_incrementOut()		{return angle_incrementOut; }
	Output<double>& getTime_incrementOut()		{return time_incrementOut; }
	Output<double>& getScan_timeOut()			{return scan_timeOut; }
	Output<double>& getRange_minOut()			{return range_minOut; }
	Output<double>& getRange_maxOut()			{return range_maxOut; }
	


protected:
	//TODO Header
	Output< double >		angle_minOut;
	Output< double >		angle_maxOut;
	Output< double >		angle_incrementOut;
	Output< double >		time_incrementOut;
	Output< double >		scan_timeOut;
	Output< double >		range_minOut;
	Output< double >		range_maxOut;
};



#endif // ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP