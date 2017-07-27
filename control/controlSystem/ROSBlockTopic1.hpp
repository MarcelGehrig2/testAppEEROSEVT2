#ifndef ROSBLOCKTOPIC1_HPP
#define ROSBLOCKTOPIC1_HPP

#include <ros/ros.h>
#include <eeros/control/ROSBlock.hpp>
#include <eeros/core/System.hpp>

// includes used for ROS message types
#include <std_msgs/Float64.h>
//#include <sensor_msgs/Joy.h>
//#include <sensor_msgs/LaserScan.h>

using namespace eeros::control;

template < typename TMsg, typename TOutput = double >
	class ROSBlockTopic1 : public ROSBlock< TMsg > {

public:
	ROSBlockTopic1(ros::NodeHandle& rosNodeHandler, const std::string& topic, uint32_t queueSize=1000) :
		rosNodeHandler(rosNodeHandler),
		ROSBlock< TMsg >( rosNodeHandler, topic, queueSize )
	{
		//clear all EEROS signals
		out.getSignal().clear();
	}


	void rosCallbackFct(const TMsg& msg) {
//			auto start = std::chrono::steady_clock::now();
//				ROS_INFO_STREAM("rosCallbackFct: '" << msg.data);
//			auto stop = std::chrono::steady_clock::now();
//			std::chrono::duration<int, std::nano> duration = stop - start;	//nsec allways int.
//			//std::chrono::duration<double, std::milli> duration = stop - start;	//cast to msec
//			std::cout << "Duration 'ROS_INFO_STREAM': " << duration.count() << " nsec" << std::endl;

//			start = std::chrono::steady_clock::now();
//				std::cout << "rosCallbackFct: '" << msg.data << std::endl;
//			stop = std::chrono::steady_clock::now();
//			duration = stop - start;	//nsec allways int.
//			//std::chrono::duration<double, std::milli> duration = stop - start;	//cast to msec
//			std::cout << "Duration 'std::cout': " << duration.count() << " nsec" << std::endl;


		// USER DEFINED: 1.) Set timestamp for all outputs
		//               2.) Get the data from the message
		//               3.) Cast the data if necessary
		//               4.) Insert the data into output

		auto time = eeros::System::getTimeNs();
		out.getSignal().setTimestamp( time );
		outValue = msg.data;
		out.getSignal().setValue(static_cast< TOutput >( outValue ) );	// depends heavily ond the type of the ROS message
	}

	// USER DEFINED: Add a 'getOut()' function for each output
	virtual eeros::control::Output< TOutput >& getOut() {
		return out;
	}

	virtual void run() {
//			ros::getGlobalCallbackQueue()->callAvailable();		// calls callback fct. for all available messages.
															//  Only newest message is processed. Older ones are discarded.
		ros::getGlobalCallbackQueue()->callOne();			// calls callback fct. only for the oldest message
		ROS_DEBUG_STREAM(outValue);
	}


protected:
	eeros::control::Output< TOutput > out;
	TOutput outValue;

	//ROS variables
	// USER DEFINED: Necessary member variables
	ros::NodeHandle& rosNodeHandler;

private:
};

#endif // ROSBLOCKTOPIC1_HPP
