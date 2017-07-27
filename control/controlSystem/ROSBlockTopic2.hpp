#ifndef ROSBLOCKTOPIC2_HPP
#define ROSBLOCKTOPIC2_HPP

#include <ros/ros.h>
#include <eeros/control/ROSBlock.hpp>
#include <eeros/core/System.hpp>
#include <eeros/math/Matrix.hpp>

// Include used message type
//#include <std_msgs/Float64.h>
#include <sensor_msgs/Joy.h>
//#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

template < typename TMsg >
class ROSBlockTopic2 : public ROSBlock< TMsg > {

	typedef eeros::math::Matrix< 3 , 1 , double >		typeAxesOutput;
	typedef eeros::math::Matrix< 5 , 1 , int >			typeButtonsOutput;

public:
	ROSBlockTopic2(ros::NodeHandle& rosNodeHandler, const std::string& topic, uint32_t queueSize=1000) :
		rosNodeHandler(rosNodeHandler),
		ROSBlock< TMsg >( rosNodeHandler, topic, queueSize )
	{
		//clear all EEROS signals
		axesOutput.getSignal().clear();
		buttonsOutput.getSignal().clear();
	}


	virtual void rosCallbackFct(const TMsg& msg) {
		auto time = eeros::System::getTimeNs();

		// USER DEFINED: 1.) Set timestamp for all outputs
		//               2.) Get the data from the message
		//               3.) Cast the data if necessary
		//               4.) Insert the data into output

		axesOutput.getSignal().setTimestamp( time );
		buttonsOutput.getSignal().setTimestamp( time );
		
		std::vector<double> tmp( msg.axes.begin(), msg.axes.end() );	//cast because axes is a float32 vector
		axesValue.setCol(0, tmp);
		axesOutput.getSignal().setValue(axesValue);

		buttonsValue.setCol(0, msg.buttons);
		buttonsOutput.getSignal().setValue(buttonsValue);
	}


	// USER DEFINED: Add a 'getOut()' function for each output
	virtual eeros::control::Output<typeAxesOutput>& getAxesOut() {
		return axesOutput;
	}


	virtual eeros::control::Output<typeButtonsOutput>& getButtonsOut() {
		return buttonsOutput;
	}


protected:
	// USER DEFINED: Necessary member variables
	eeros::control::Output<typeAxesOutput> axesOutput;
	typeAxesOutput axesValue;
	eeros::control::Output<typeButtonsOutput> buttonsOutput;
	typeButtonsOutput buttonsValue;

	//ROS variables
	ros::NodeHandle& rosNodeHandler;

private:
};

#endif /* ROSBLOCKTOPIC2_HPP */
