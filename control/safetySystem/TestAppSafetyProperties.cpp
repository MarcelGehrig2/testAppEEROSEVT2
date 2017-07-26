#include "TestAppSafetyProperties.hpp"
#include "../controlSystem/TestAppCS.hpp"
 
#include <eeros/hal/HAL.hpp>
#include <eeros/safety/InputAction.hpp>
#include <eeros/safety/OutputAction.hpp>
#include <eeros/core/Executor.hpp>
 
#include <iostream>
 
using namespace testapp; 
using namespace eeros;
using namespace eeros::hal;
using namespace eeros::control;
using namespace eeros::safety;
 
TestAppSafetyProperties::TestAppSafetyProperties(TestAppCS* cs) :
controlSys(cs),
log('S'),

  // Levels
slOff					("System off"),
slShuttingDown			("shutting down"),
slIinitializing			("initializing"),
slInitialized			("initialized"),
slRunning				("running"),

// Events
seStartInitializing		("start initializing"),
seStartRunning			("start running"),
seShutDown				("start shutting down"),
seStopRunning			("start stop running"),
seSwitchingOff			("start switching off")
{
	// ############ Add levels ############
	addLevel(slOff);
	addLevel(slShuttingDown);
	addLevel(slIinitializing);
	addLevel(slInitialized);
	addLevel(slRunning);

	// ############ Add events to the levels ############
	slIinitializing.addEvent(	seStartInitializing,	slInitialized,				kPrivateEvent);
	slInitialized.addEvent(		seStartRunning,			slRunning,					kPrivateEvent);
	slRunning.addEvent(			seStopRunning,			slShuttingDown,				kPrivateEvent);
	slShuttingDown.addEvent(	seSwitchingOff,			slOff,						kPrivateEvent);

	addEventToLevelAndAbove(	slInitialized,	seShutDown, slShuttingDown, kPublicEvent);
 
	// Define and add level functions
	slIinitializing.setLevelAction([&](SafetyContext* privateContext) {
		privateContext->triggerEvent(seStartInitializing);
	});
	slOff.setLevelAction([&](SafetyContext* privateContext) {
		Executor::stop();
	});
	slShuttingDown.setLevelAction([&](SafetyContext* privateContext) {
		privateContext->triggerEvent(seSwitchingOff);
	});
	slInitialized.setLevelAction([&](SafetyContext* privateContext) {
		privateContext->triggerEvent(seStartRunning);
	});

	// Define entry level
	setEntryLevel(slIinitializing);

	// Define action when exiting application with Ctrl-C
	exitFunction = [&](SafetyContext* privateContext) {
		log.trace() << "exitFunction";
		privateContext->triggerEvent(seShutDown);
	};
}
 
TestAppSafetyProperties::~TestAppSafetyProperties() {
   // nothing to do
}

