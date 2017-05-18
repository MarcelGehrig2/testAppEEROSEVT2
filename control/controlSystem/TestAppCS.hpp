#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_


#include <ros/ros.h>
#include <eeros/control/TimeDomain.hpp> 

#include <eeros/control/Constant.hpp>
#include <eeros/control/ReceiveTeleopTurtleKey.hpp>
#include "Print.hpp"


using namespace eeros::control;

namespace testapp {
	
	class TestAppCS {		
	public:
//		TestAppCS(double dt);
		TestAppCS(double dt, ros::NodeHandle& rosNodeHandler);
		
		std::string test = "test erfolgreich";
		
		// Define blocks
		Constant<int> constIntA;
		Print<int> printIntA;
		ReceiveTeleopTurtleKey receiveKeyboard;
		
		
// 		float maxPeriod[1000] = {0};
// 		static constexpr double dt = 0.01;
				
//	protected:
		double dt;
		ros::NodeHandle& rosNodeHandler;
		bool realtime;
		eeros::control::TimeDomain timedomain;
	}; // END class
	
}; // END namespace

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
