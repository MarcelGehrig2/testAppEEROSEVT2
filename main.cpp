#include <iostream>
#include <signal.h>

#include <ros/console.h>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sstream>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include <eeros/logger/Logger.hpp>
#include <eeros/logger/StreamLogWriter.hpp>

#include <eeros/logger/ROSLogWriter.hpp>

#include "control/controlSystem/TestAppCS.hpp"
#include "control/safetySystem/TestAppSafetyProperties.hpp"

using namespace eeros;
using namespace eeros::logger;
using namespace testapp;

bool threadFinishd = false;


volatile bool running = true;
void signalHandler(int signum) {
	std::cout << "main: signalHandler" << std::endl;
	running = false;
//	ros::shutdown();
	SafetySystem::exitHandler();
}


int main(int argc, char **argv) {

//	ros::init(argc, argv, "talker");
//	ros::NodeHandle n;
//	signal(SIGINT, signalHandler);		// Needs to be set after initialization of ROS
//	ROS_INFO("%s", "Hello World");
//	ROS_DEBUG("Hello %s", "World");
	
	double dt = 0.5;
	
	StreamLogWriter w(std::cout);
	w.show(LogLevel::TRACE);
	Logger::setDefaultWriter(&w);
	Logger log;

 
	log.info() << "EEROS started";
	
	// Executor
	// ////////////////////////////////////////////////////////////////////////
	auto &executor = eeros::Executor::instance();

	// ROS
	// ////////////////////////////////////////////////////////////////////////
	char* dummy_args[] = {NULL};
	int dummy_argc = sizeof(dummy_args)/sizeof(dummy_args[0]) - 1;
	ros::init(dummy_argc, dummy_args, "EEROSNode");
	log.trace() << "ROS node initialized.";
	ros::NodeHandle rosNodeHandler;
//	rosNodeHandle ros::NodeHandle;
	
	
	// Control System
	// ////////////////////////////////////////////////////////////////////////
	testapp::TestAppCS controlSystem (dt, rosNodeHandler);

	// Lambda function for logging signals in CS
	// /////////////////////////////////////////
	eeros::task::Lambda l1 ([&] () { });
	eeros::task::Periodic perLog("periodic log", 0.5, l1);
	perLog.monitors.push_back([&](PeriodicCounter &pc, Logger &log){
		log.info() << "ROSTopic 1: " << controlSystem.rosBlockA.getOut().getSignal();
		log.info() << "ROSTopic 2 Axes: " << controlSystem.rosBlockB.getAxesOut().getSignal();
		log.info() << "ROSTopic 2 Buttons: " << controlSystem.rosBlockB.getButtonsOut().getSignal();
	});
	executor.add(perLog);
	
	// Safety System
	// ////////////////////////////////////////////////////////////////////////
	TestAppSafetyProperties safetyProperties(&controlSystem);
	eeros::safety::SafetySystem safetySystem(safetyProperties, dt);
	

	// Timing measurements
	// ///////////////////
	typedef std::chrono::steady_clock clock;
	auto start = clock::now();
	auto stop = clock::now();
	std::chrono::duration<int, std::nano> duration;
	int i;

	// Performance Measurements EEROS logger
#include "measurementsEEROSLogger.hpp"


	executor.setMainTask(safetySystem);
	
	
//// 	// Sequencer
//// 	// ////////////////////////////////////////////////////////////////////////
//// 	eeros::sequencer::Sequencer S;
//// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
//// 	S.addMainSequence(&mainSequence);
	
	signal(SIGINT, signalHandler);		// Needs to be set after initialization of ROS
	log.info() << "executor.run()";
	executor.run();

//	threadFinishd = true;
	
//		sleep(10);
	return 0;
}
