#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Lambda.hpp>
#include <eeros/task/Periodic.hpp>

#include "TestAppCS.hpp"

using namespace testapp;
using namespace eeros::control;
using namespace std;


//TestAppCS::TestAppCS(double dt, ros::NodeHandle& rosNodeHandler) :
TestAppCS::TestAppCS(double dt) :
dt(dt),
//rosNodeHandler(rosNodeHandler),

printDouble0(1),
printBool0(1),
//rosBlockA(rosNodeHandler, "/testNode/TestTopic1"),
//rosBlockB(rosNodeHandler, "/testNode/TestTopic2"),
analogIn0("scanTimeIn0"),
digitalIn0("batteryPresent0"),
analogOut0("scanTimeEchoOut0"),
digitalOut0("batteryPresentEchoOut0"),

timedomain("Main time domain", dt, true)

{
		
	// Connect Blocks
//	printIntA.getIn().connect(rosBlockA.getOut());
	printDouble0.getIn().connect(analogIn0.getOut());
	printBool0.getIn().connect(digitalIn0.getOut());
	analogOut0.getIn().connect(analogIn0.getOut());
	digitalOut0.getIn().connect(digitalIn0.getOut());

			
	
	// Monitor for logging

	// Run blocks
	timedomain.addBlock(&analogIn0);
	timedomain.addBlock(&digitalIn0);
//	timedomain.addBlock(&rosInScanTime0);
//	timedomain.addBlock(&rosBlockA);
//	timedomain.addBlock(&anOut0);
//	timedomain.addBlock(&rosBlockB);
	timedomain.addBlock(&printDouble0);
	timedomain.addBlock(&printBool0);
	timedomain.addBlock(&analogOut0);
	timedomain.addBlock(&digitalOut0);
// 				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
