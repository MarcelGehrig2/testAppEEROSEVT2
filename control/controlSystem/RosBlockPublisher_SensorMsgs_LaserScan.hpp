#ifndef ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP
#define ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP

#include <eeros/control/RosBlockPublisher.hpp>
#include <eeros/math/Matrix.hpp>
#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

typedef sensor_msgs::LaserScan::Type	TRosMsg;


template < typename TRangesInput, typename TIntensitiesInput >
class RosBlockPublisher_SensorMsgs_LaserScan : public RosBlockPublisher< TRosMsg > {
public:
	RosBlockPublisher_SensorMsgs_LaserScan(ros::NodeHandle& rosNodeHandler, const std::string& topic, const uint32_t queueSize=1000) :
		RosBlockPublisher< TRosMsg >( rosNodeHandler, topic, queueSize )
		{}
		
	void setRosMsg(TRosMsg& msg) {
		//TODO time header
		if (angle_minInput.isConnected() )
			msg.angle_min		= static_cast<float>( angle_minInput.getSignal().getValue() );
		if (angle_maxInput.isConnected() )
			msg.angle_max 		= static_cast<float>( angle_maxInput.getSignal().getValue() );
		if (angle_incrementInput.isConnected() )
			msg.angle_increment = static_cast<float>( angle_incrementInput.getSignal().getValue() );
		if (time_incrementInput.isConnected() )
			msg.time_increment	= static_cast<float>( time_incrementInput.getSignal().getValue() );
		if (scan_timeInput.isConnected() )
			msg.scan_time		= static_cast<float>( scan_timeInput.getSignal().getValue() );
		if (range_minInput.isConnected() )
			msg.range_min		= static_cast<float>( range_minInput.getSignal().getValue() );
		if (range_maxInput.isConnected() )
			msg.range_max		= static_cast<float>( range_maxInput.getSignal().getValue() );
		// vectors
		sleep(1);
		if (rangesInput.isConnected() ) {
			rangesValue = rangesInput.getSignal().getValue();
			auto rangesTmpDouble = rangesValue.getColVector(0);
			std::vector<float> rangesTmpFloat( rangesTmpDouble.begin(), rangesTmpDouble.end() );	// cast to float vector
			msg.ranges			= rangesTmpFloat;
		}
		if (intensitiesInput.isConnected() ) {
			intensitiesValue = intensitiesInput.getSignal().getValue();
			auto intensitiesTmpDouble = rangesValue.getColVector(0);
			std::vector<float> intensitiesTmpFloat( intensitiesTmpDouble.begin(), intensitiesTmpDouble.end() );	// cast to float vector
			msg.ranges			= intensitiesTmpFloat;
		}
	}
	
	Input<double>& getAngle_minInput()			{return angle_minInput; };
	Input<double>& getAngle_maxInput()			{return angle_maxInput; };
	Input<double>& getAngle_incrementInput()	{return angle_incrementInput; };
	Input<double>& getTime_incrementInput()	{return time_incrementInput; };
	Input<double>& getScan_timeInput()			{return scan_timeInput; };
	Input<double>& getRange_minInput()			{return range_minInput; };
	Input<double>& getRange_maxInput()			{return range_maxInput; };
	Input<TRangesInput>& getRangesInput()				{return rangesInput; };
	Input<TIntensitiesInput>& getIntensitiessInput()	{return intensitiesInput; };
		
protected:
	Input<double> angle_minInput;
	Input<double> angle_maxInput;
	Input<double> angle_incrementInput;
	Input<double> time_incrementInput;
	Input<double> scan_timeInput;
	Input<double> range_minInput;
	Input<double> range_maxInput;
	TRangesInput				rangesValue;
	Input<TRangesInput>			rangesInput;
	TIntensitiesInput			intensitiesValue;
	Input<TIntensitiesInput>	intensitiesInput;
};


#endif // ROSBLOCKPUBLISHER_SENSORMSGS_LASERSCAN_HPP