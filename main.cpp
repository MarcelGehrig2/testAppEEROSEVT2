#include <iostream>
#include <signal.h>

#include <ros/console.h>
#include <ros/ros.h>
#include "std_msgs/String.h"
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

using namespace eeros;
using namespace eeros::logger;


void signalHandler(int signum) {
	Executor::stop();
}

int main(int argc, char **argv) {
	double dt = 0.2;
	
	// Create and initialize logger
	// ////////////////////////////////////////////////////////////////////////
	StreamLogWriter w(std::cout);
	Logger::setDefaultWriter(&w);
	Logger log;
	w.show();
 
	log.info() << "EEROS started";

	// HAL
	// ////////////////////////////////////////////////////////////////////////
// 	HAL& hal = HAL::instance();
// 	hal.readConfigFromFile(&argc, argv);

	// ROS
	// ////////////////////////////////////////////////////////////////////////
	char* dummy_args[] = {NULL};
	int dummy_argc = sizeof(dummy_args)/sizeof(dummy_args[0]) - 1;
	ros::init(dummy_argc, dummy_args, "EEROSNode");
	log.trace() << "ROS node initialized.";
	ros::NodeHandle rosNodeHandler;
		
	// Control System
	// ////////////////////////////////////////////////////////////////////////
	MyControlSystem controlSystem(dt, rosNodeHandler);
	
	// Safety System
	// ////////////////////////////////////////////////////////////////////////
	MySafetyProperties safetyProperties;
	eeros::safety::SafetySystem safetySystem(safetyProperties, dt);

//	rosNodeHandler.setParam("/use_sim_time", true);		// sumulation time (i.e. with gazebo)
//	rosNodeHandle ros::NodeHandle;
	
	
//	// Lambda function for logging signals in CS
//	// /////////////////////////////////////////
//	eeros::task::Lambda l1 ([&] () { });
//	eeros::task::Periodic perLog("periodic log", 0.5, l1);
//	perLog.monitors.push_back([&](PeriodicCounter &pc, Logger &log){
//		log.info() << "ROSTopic 1: " << controlSystem.rosBlockA.getOut().getSignal();
////		log.info() << "ROSTopic 2 Axes: " << controlSystem.rosBlockB.getAxesOut().getSignal();
////		log.info() << "ROSTopic 2 Buttons: " << controlSystem.rosBlockB.getButtonsOut().getSignal();
//	});
//	executor.add(perLog);
	
	
//// 	// Sequencer
//// 	// ////////////////////////////////////////////////////////////////////////
//// 	eeros::sequencer::Sequencer S;
//// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
//// 	S.addMainSequence(&mainSequence);
	
	
	// Executor
	// ////////////////////////////////////////////////////////////////////////
	signal(SIGINT, signalHandler);	
	auto &executor = Executor::instance();
	executor.setMainTask(safetySystem);
	executor.run();
	
	return 0;
}
