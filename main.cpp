#include <iostream>
#include <signal.h>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include <eeros/logger/Logger.hpp>
#include <eeros/logger/StreamLogWriter.hpp>


#include "control/controlSystem/TestAppCS.hpp"
#include "control/safetySystem/TestAppSafetyProperties.hpp"

using namespace eeros;
using namespace eeros::logger;
using namespace testapptcpip;

bool threadFinishd = false;


volatile bool running = true;
void signalHandler(int signum) {
	running = false;
}


int main(int argc, char **argv) {
	signal(SIGINT, signalHandler);
	
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
// 	TestAppCS controlSystem; 
	testapptcpip::TestAppCS controlSystem (dt);
	
	// Safety System
	// ////////////////////////////////////////////////////////////////////////
	TestAppSafetyProperties safetyProperties(&controlSystem);
	eeros::safety::SafetySystem safetySystem(safetyProperties, dt);
	
	executor.setMainTask(safetySystem);
	
	
// 	// Sequencer
// 	// ////////////////////////////////////////////////////////////////////////
// 	eeros::sequencer::Sequencer S;
// 	MainSequence mainSequence(S, &controlSystem, "mainSequence");
// 	S.addMainSequence(&mainSequence);
	
	log.info() << "executor.run()";
	executor.run();

	threadFinishd = true;
	
	return 0;
}