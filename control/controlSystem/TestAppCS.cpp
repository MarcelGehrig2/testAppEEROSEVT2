#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include <eeros/core/PeriodicCounter.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/task/Periodic.hpp>
#include <eeros/hal/HAL.hpp>
#include <ros/console.h>

#include "TestAppCS.hpp"

using namespace testapp;
using namespace eeros::control;
using namespace std;


TestAppCS::TestAppCS(double dt, ros::NodeHandle& rosNodeHandler) :
dt(dt),
rosNodeHandler(rosNodeHandler),
	
constIntA(4),
constDoubleA(2.2),
printIntA(1),
printDoubleA(1),
//receiveKeyboard(rosNodeHandler),
rosBlockA(rosNodeHandler, "/testNode/TestTopic1"),
//rosBlockB(rosNodeHandler, "/testNode/TestTopic2"),
anOut0("aOut0"),
anIn0("/testNode/TestTopic1"),

timedomain("Main time domain", dt, true)

{
		
	// Connect Blocks
//	printIntA.getIn().connect(rosBlockA.getOut());
	printDoubleA.getIn().connect(anIn0.getOut());
	anOut0.getIn().connect(rosBlockA.getOut());

			
	
	// Monitor for logging

	// Run blocks
	timedomain.addBlock(&anIn0);
	timedomain.addBlock(&constIntA);
//	timedomain.addBlock(&printIntA);
//	timedomain.addBlock(&receiveKeyboard);
	timedomain.addBlock(&rosBlockA);
	timedomain.addBlock(&anOut0);
//	timedomain.addBlock(&rosBlockB);
	timedomain.addBlock(&printDoubleA);
// 				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
