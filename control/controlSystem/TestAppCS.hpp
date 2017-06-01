#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_


#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Joy.h>
#include <eeros/control/TimeDomain.hpp> 

#include <eeros/control/Constant.hpp>

#include "Print.hpp"
#include <std_msgs/Float64.h>
#include "ROSBlockTopic1.hpp"
#include "ROSBlockTopic2.hpp"

using namespace eeros::control;

namespace testapp {
	
	class TestAppCS {		
	public:
//		TestAppCS(double dt);
		TestAppCS(double dt, ros::NodeHandle& rosNodeHandler);
		
		std::string test = "test erfolgreich";
		
		// Define blocks
		Constant<int> constIntA;
		Print<double> printIntA;
		ROSBlockTopic1< std_msgs::Float64::Type, double > rosBlockA;
		ROSBlockTopic2< sensor_msgs::Joy::Type > rosBlockB;
				
//	protected:
		double dt;
		ros::NodeHandle& rosNodeHandler;
		bool realtime;
		eeros::control::TimeDomain timedomain;
	}; // END class
	
} // END namespace

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
