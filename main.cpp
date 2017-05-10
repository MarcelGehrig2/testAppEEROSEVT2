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
	SafetySystem::exitHandler();
}


int main(int argc, char **argv) {


	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	signal(SIGINT, signalHandler);		// Needs to be set after initialization of ROS
	ROS_INFO("%s", "Hello World");
	ROS_DEBUG("Hello %s", "World");
	
	double dt = 0.001;
	
	StreamLogWriter w(std::cout);
	w.show(LogLevel::TRACE);
	Logger::setDefaultWriter(&w);
	Logger log;
 
	log.info() << "EEROS started";
	
	// Executor
	// ////////////////////////////////////////////////////////////////////////
	auto &executor = eeros::Executor::instance();
	
	
	// Control System
	// ////////////////////////////////////////////////////////////////////////
	testapp::TestAppCS controlSystem (dt);
	
	// Safety System
	// ////////////////////////////////////////////////////////////////////////
	TestAppSafetyProperties safetyProperties(&controlSystem);
	eeros::safety::SafetySystem safetySystem(safetyProperties, dt);
	
	executor.setMainTask(safetySystem);
	
	
//// 	// Sequencer
//// 	// ////////////////////////////////////////////////////////////////////////
//// 	eeros::sequencer::Sequencer S;
//// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
//// 	S.addMainSequence(&mainSequence);
	
	log.info() << "executor.run()";
	executor.run();

//	threadFinishd = true;
	
//		sleep(10);
	return 0;
}
