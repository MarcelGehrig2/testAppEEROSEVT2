#include <iostream>
#include <signal.h>

#include <ros/console.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <sstream>

#include <eeros/hal/HAL.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/core/RosTopicSynchronizer.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include <eeros/logger/Logger.hpp>
#include <eeros/logger/StreamLogWriter.hpp>

#include <eeros/logger/ROSLogWriter.hpp>

#include "control/controlSystem/MyControlSystem.hpp"
#include "control/safetySystem/MySafetyProperties.hpp"





#include <std_msgs/Float64.h>




using namespace eeros;
using namespace eeros::logger;


void signalHandler(int signum) {
	
	Executor::stop();
}

// void callback(const std_msgs::Float64::Type){
void callback(const sensor_msgs::JointState::Type){
// 	std::cout << "callback" << std::endl;
};

template <typename msgType>
class callbackFunctor {
public:
  void operator()(const msgType& message) { return; };
// 	callbackFunctor<>
	
};

class Foo
{
public:
  void operator()(const std_msgs::StringConstPtr& message)
  {
  }
};

template<typename msgType>
void callbackDummy(const msgType type) {}

int main(int argc, char **argv) {
	double dt = 0.001;
	
	// Create and initialize logger
	// ////////////////////////////////////////////////////////////////////////
	StreamLogWriter w(std::cout);
	Logger::setDefaultWriter(&w);
	Logger log;
	w.show();
 
	log.info() << "EEROS started";
	
	// HAL
	// ////////////////////////////////////////////////////////////////////////
	HAL& hal = HAL::instance();
	hal.readConfigFromFile(&argc, argv);

	// ROS
	// ////////////////////////////////////////////////////////////////////////
	char* dummy_args[] = {NULL};
	int dummy_argc = sizeof(dummy_args)/sizeof(dummy_args[0]) - 1;
	ros::init(dummy_argc, dummy_args, "motor_sim");
	ros::NodeHandle rosNodeHandler;
	log.trace() << "ROS node initialized.";
	
	
// 	ros::NodeHandle syncNodeHandler;
// 	ros::CallbackQueue syncCallbackQueue;
// 	syncNodeHandler.setCallbackQueue(&syncCallbackQueue);
// 	auto subscriberSync = syncNodeHandler.subscribe("motor_sim/joint_states", 1, &callback);
// 	
		
	// Control System
	// ////////////////////////////////////////////////////////////////////////
	MyControlSystem controlSystem(dt, rosNodeHandler);
	
	// Safety System
	// ////////////////////////////////////////////////////////////////////////
	MySafetyProperties safetyProperties;
	eeros::safety::SafetySystem safetySystem(safetyProperties, dt);
	
	
	// Executor
	// ////////////////////////////////////////////////////////////////////////
	signal(SIGINT, signalHandler);	
	auto &executor = Executor::instance();
	executor.setMainTask(safetySystem);
	
	
// 	executor.syncWithRosTopic(&syncCallbackQueue);
// 	eeros::System::useRosTime();
	
	
	// Lambda function for logging signals in CS
	// /////////////////////////////////////////
//	eeros::task::Lambda l1 ([&] () { });
//	eeros::task::Periodic perLog("periodic log", 0.001, l1);
//	perLog.monitors.push_back([&](PeriodicCounter &pc, Logger &log){
//		log.info() << "motor Position in: " << controlSystem.motorPositionIn0.getOut().getSignal();
//		log.info() << "posToVelIn:        ; " << controlSystem.posToVel.getIn().getSignal();
//		log.info() << "posToVel        : " << controlSystem.posToVel.getOut().getSignal();
//		log.info() << "ROSTopic 2 Buttons: " << controlSystem.rosBlockB.getButtonsOut().getSignal();
//	});
//	executor.add(perLog);
	
	
//// 	// Sequencer
//// 	// ////////////////////////////////////////////////////////////////////////
//// 	eeros::sequencer::Sequencer S;
//// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
//// 	S.addMainSequence(&mainSequence);
	executor.run();
	
	return 0;
}
