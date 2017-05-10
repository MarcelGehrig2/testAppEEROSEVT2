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
    // Create HAL instance
 //   HAL& hal = HAL::instance();
 
    // ***** Define critical outputs ***** //
//     watchdog = hal.getLogicPeripheralOutput("watchdog");
//     criticalOutputs = {watchdog};
 
    // ***** Define critical inputs ***** //
//     emergencyButton = hal.getLogicPeripheralInput("emergencyButton");
//     criticalInputs = {emergencyButton};
 
    // ***** Define levels ***** //
// // 	enum {
// // 		off = 1,
// // 		running = 2,
// // 	};
// //   
// // 	levels = 	{
// // 				{off,       	"system off",		},
// // 				{running,	"system running ",	},
// // 	};
// //  
	// ############ Add events to the levels ############
	slIinitializing.addEvent(	seStartInitializing,	slInitialized,				kPrivateEvent);
	slInitialized.addEvent(		seStartRunning,			slRunning,					kPrivateEvent);
	slRunning.addEvent(			seStopRunning,			slShuttingDown,				kPrivateEvent);
	slShuttingDown.addEvent(	seSwitchingOff,			slOff,						kPrivateEvent);

	addEventToLevelAndAbove(	slInitialized,	seShutDown, slShuttingDown, kPublicEvent);
 
    // ***** Define inputs actions ***** //
//      level(off      ).setInputActions({ ignore(emergencyButton), ignore(encoder)});
 
    // ***** Define output actions ***** //
//      level(off      ).setOutputActions({ set(watchdog, false), set(enable, false)});
 
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
	slRunning.setLevelAction([&](SafetyContext* privateContext){
//		privateContext->triggerEvent(se);
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

