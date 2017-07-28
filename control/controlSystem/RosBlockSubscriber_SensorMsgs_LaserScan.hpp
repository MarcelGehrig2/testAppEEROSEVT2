#ifndef ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP
#define ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP

// #include <ros/ros.h>
#include <eeros/control/RosBlockSubscriber.hpp>
#include <eeros/core/System.hpp>

#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

typedef sensor_msgs::LaserScan::Type	TRosMsg;

//B1
template < typename TRangesOutput, typename TIntensitiesOutput >
class RosBlockSubscriber_SensorMsgs_LaserScan : public RosBlockSubscriber< TRosMsg > {
public:
	RosBlockSubscriber_SensorMsgs_LaserScan(ros::NodeHandle& rosNodeHandler,
											const std::string& topic,
											const uint32_t queueSize=1000,
											const bool callNewest=false ) :
		RosBlockSubscriber< TRosMsg >( rosNodeHandler, topic, queueSize, callNewest )
		{}
		
	void rosCallbackFct(const TRosMsg& msg) {
		// USER DEFINED: 1.) Set timestamp for all outputs
		//               2.) Get the data from the message
		//               3.) Cast the data if necessary
		//               4.) Insert the data into output

		
		// TODO timing from header
		auto time = eeros::System::getTimeNs();
		angle_minOutput.getSignal().setTimestamp( time );
		angle_maxOutput.getSignal().setTimestamp( time );
		angle_incrementOutput.getSignal().setTimestamp( time );
		time_incrementOutput.getSignal().setTimestamp( time );
		scan_timeOutput.getSignal().setTimestamp( time );
		range_minOutput.getSignal().setTimestamp( time );
		range_maxOutput.getSignal().setTimestamp( time );
		
		// set value
		angle_minOutput.getSignal().setValue(			static_cast< double > ( msg.angle_min ) );
		angle_maxOutput.getSignal().setValue(			static_cast< double > ( msg.angle_max ) );
		angle_incrementOutput.getSignal().setValue(	static_cast< double > ( msg.angle_increment ) );
		time_incrementOutput.getSignal().setValue(		static_cast< double > ( msg.time_increment ) );
		scan_timeOutput.getSignal().setValue(			static_cast< double > ( msg.scan_time ) );
		range_minOutput.getSignal().setValue(			static_cast< double > ( msg.range_min ) );
		range_maxOutput.getSignal().setValue(			static_cast< double > ( msg.range_max ) );
		
		// B4 set value for vectors
		std::vector<double> rangesTmp( msg.ranges.begin(), msg.ranges.end() );	//cast because axes is a float32 vector
		rangesValue.setCol(0, rangesTmp);
		rangesOutput.getSignal().setValue(rangesValue);
		std::vector<double> intensitiesTmp( msg.intensities.begin(), msg.intensities.end() );	//cast because axes is a float32 vector
		intensitiesValue.setCol(0, intensitiesTmp);
		intensitiesOutput.getSignal().setValue(intensitiesValue);
	}

	// USER DEFINED: Add a 'getOutput()' function for each output
	Output<double>& getAngle_minOutput()			{return angle_minOutput; }
	Output<double>& getAngle_maxOutput()			{return angle_maxOutput; }
	Output<double>& getAngle_incrementOutput()		{return angle_incrementOutput; }
	Output<double>& getTime_incrementOutput()		{return time_incrementOutput; }
	Output<double>& getScan_timeOutput()			{return scan_timeOutput; }
	Output<double>& getRange_minOutput()			{return range_minOutput; }
	Output<double>& getRange_maxOutput()			{return range_maxOutput; }
	//B3
	Output<TRangesOutput>& getRangesOutput()			{return rangesOutput; }
	Output<TIntensitiesOutput>& getIntensitiesOutput()	{return intensitiesOutput; }
	


protected:
	//TODO Header
	Output<double>		angle_minOutput;
	Output<double>		angle_maxOutput;
	Output<double>		angle_incrementOutput;
	Output<double>		time_incrementOutput;
	Output<double>		scan_timeOutput;
	Output<double>		range_minOutput;
	Output<double>		range_maxOutput;
	//B2
	TRangesOutput				rangesValue;
	Output<TRangesOutput>		rangesOutput;
	TIntensitiesOutput			intensitiesValue;
	Output<TIntensitiesOutput>	intensitiesOutput;
};



#endif // ROSBLOCKSUBSCRIBER_SENSORMSGS_LASERSCAN_HPP