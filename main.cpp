#include <iostream>
#include <signal.h>

#include <ros/console.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <sstream>

#include <eeros/hal/HAL.hpp>
#include <eeros/core/Executor.hpp>
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
	std::cout << "callback" << std::endl;
};

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
// 	ros::init(dummy_argc, dummy_args, "EEROSNode");
	ros::init(dummy_argc, dummy_args, "motor_sim");
	ros::NodeHandle rosNodeHandler;
	log.trace() << "ROS node initialized.";
	
// 	 void rosCallbackFct(const std_msgs::Float64::Type& msg);
// 	ros::Subscriber subscriber = rosNodeHandler.subscribe("rosNodeTalker/TestTopic1", 
// 	ros::Subscriber subscriber = rosNodeHandler.subscribe("rosNodeTalker/TestTopic1",1,)
	ros::NodeHandle syncNodeHandler;
	ros::CallbackQueue syncCallbackQueue;
	syncNodeHandler.setCallbackQueue(&syncCallbackQueue);
// 	void dummyLambda = [](std_msgs::Float64::Type){};
// 	void callback(const std_msgs::Float64::Type){};
// 	auto func = [] (std_msgs::Float64::Type) { std::cout << "Hello world"; };
// 	auto subscriberSync = syncNodeHandler.subscribe("rosNodeTalker/TestTopic1", 1, &callback);
	auto subscriberSync = syncNodeHandler.subscribe("motor_sim/joint_states", 1, &callback);
	
// // 	syncCallbackQueue.callAvailable(ros::WallDuration());
// // 	std::cout << "syncCallbackQueue.callOne(): " << std::endl;
// 	while(true) {
// 		auto value = syncCallbackQueue.isEmpty();
// 		std::cout << "syncCallbackQueue.isEmpty(): " << value << std::endl;
// // 		std::cout << "number of publisher: " << subscriberSync.getNumPublishers() << std::endl;
// // 		syncCallbackQueue.callAvailable(ros::WallDuration());
// // 		syncCallbackQueue.callAvailable();
// 		usleep(100000);
// 	}
	
	// 0.0 / 0		-nanVVv
	// 0 / 0.0		-nan
	// 0.0 / 0.0	-nan
	// 0 / 0		Floating point exception
	// -0 / 0.0		-nan
	// -0.0 / 0		-nan
	// -0.0 / 0.0	-nan	
	// -0 / 0		Floating point exception
	
	
// 	rosNodeHandler.setParam("/use_sim_time", true);		// sumulation time (i.e. with gazebo)
//	rosNodeHandle ros::NodeHandle;
	
		
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
	executor.syncWithGazebo(&syncCallbackQueue);
// 	executor.s
// 	executor.useRosTimeForExecutor();
	
	
	// Lambda function for logging signals in CS
	// /////////////////////////////////////////
	eeros::task::Lambda l1 ([&] () { });
	eeros::task::Periodic perLog("periodic log", 0.5, l1);
	perLog.monitors.push_back([&](PeriodicCounter &pc, Logger &log){
		log.info() << "motor Position in: " << controlSystem.motorPositionIn0.getOut().getSignal();
		log.info() << "posToVel0        : " << controlSystem.posToVel0.getOut().getSignal();
		log.info() << "analogIn:        ; " << controlSystem.analogIn0.getOut().getSignal();
//		log.info() << "ROSTopic 2 Buttons: " << controlSystem.rosBlockB.getButtonsOut().getSignal();
	});
	executor.add(perLog);
	
	
//// 	// Sequencer
//// 	// ////////////////////////////////////////////////////////////////////////
//// 	eeros::sequencer::Sequencer S;
//// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
//// 	S.addMainSequence(&mainSequence);
	executor.run();
	
	return 0;
}
