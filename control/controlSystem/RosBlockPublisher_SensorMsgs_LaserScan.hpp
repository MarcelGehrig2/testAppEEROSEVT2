#ifndef ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP
#define ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP

#include <eeros/control/RosBlockPublisher.hpp>

#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

typedef sensor_msgs::LaserScan::Type	TRosMsg;


class RosBlockPublisher_SensorMsgs_LaserScan : public RosBlockPublisher< TRosMsg > {
public:
	RosBlockPublisher_SensorMsgs_LaserScan(ros::NodeHandle& rosNodeHandler, const std::string& topic, const uint32_t queueSize=1000) :
		RosBlockPublisher< TRosMsg >( rosNodeHandler, topic, queueSize )
		{}
		
	void setRosMsg(TRosMsg& msg) {
		//TODO time header
		if (angle_minIn.isConnected() )
			msg.angle_min		= static_cast<float>( angle_minIn.getSignal().getValue() );
		if (angle_maxIn.isConnected() )
			msg.angle_max 		= static_cast<float>( angle_maxIn.getSignal().getValue() );
		if (angle_incrementIn.isConnected() )
			msg.angle_increment = static_cast<float>( angle_incrementIn.getSignal().getValue() );
		if (time_incrementIn.isConnected() )
			msg.time_increment	= static_cast<float>( time_incrementIn.getSignal().getValue() );
		if (scan_timeIn.isConnected() )
			msg.scan_time		= static_cast<float>( scan_timeIn.getSignal().getValue() );
		if (range_minIn.isConnected() )
			msg.range_min		= static_cast<float>( range_minIn.getSignal().getValue() );
		if (range_maxIn.isConnected() )
			msg.range_max		= static_cast<float>( range_maxIn.getSignal().getValue() );
	}
	
	Input<double>& getAngle_minIn()			{return angle_minIn; };
	Input<double>& getAngle_maxIn()			{return angle_maxIn; };
	Input<double>& getAngle_incrementIn()	{return angle_incrementIn; };
	Input<double>& getTime_incrementIn()	{return time_incrementIn; };
	Input<double>& getScan_timeIn()			{return scan_timeIn; };
	Input<double>& getRange_minIn()			{return range_minIn; };
	Input<double>& getRange_maxIn()			{return range_maxIn; };
		
protected:
	Input<double> angle_minIn;
	Input<double> angle_maxIn;
	Input<double> angle_incrementIn;
	Input<double> time_incrementIn;
	Input<double> scan_timeIn;
	Input<double> range_minIn;
	Input<double> range_maxIn;
};


#endif // ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP