

#include "TestAppSafetyProperties.hpp"
#include "../controlSystem/TestAppCS.hpp"
 
#include <eeros/hal/HAL.hpp>
#include <eeros/safety/InputAction.hpp>
#include <eeros/safety/OutputAction.hpp>
 
#include <iostream>
 
using namespace testapptcpip; 
using namespace eeros::hal;
using namespace eeros::control;
using namespace eeros::safety;
 
TestAppSafetyProperties::TestAppSafetyProperties(TestAppCS* cs)
: controlSys(cs), off("System off") {
	
	std::cout << "Constructor: TestAppSafetyProperties" << std::endl;

	addLevel(off);
	setEntryLevel(off);
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
    // ***** Add events to levels ***** //
//     level(off      ).addEvent(doPowerUp, poweredUp, kPublicEvent);
 
    // ***** Define inputs actions ***** //
//      level(off      ).setInputActions({ ignore(emergencyButton), ignore(encoder)});
 
    // ***** Define output actions ***** //
//      level(off      ).setOutputActions({ set(watchdog, false), set(enable, false)});
 
    // ***** Define level functions ***** //
// 	level(off).setLevelAction([&](SafetyContext* privateContext) {
// 		controlSys->start();
// // 	privateContext->triggerEvent(doPowerUp);
//     });
 
// //     entryLevel = off;
    
    
}
 
TestAppSafetyProperties::~TestAppSafetyProperties() {
   // nothing to do
}

