#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Periodic.hpp>
#include <ros/console.h>

#include "TestAppCS.hpp"

using namespace testapp;
using namespace eeros::control;
using namespace std;

TestAppCS::TestAppCS(double dt, ros::NodeHandle& rosNodeHandler) :
dt(dt),
rosNodeHandler(rosNodeHandler),
	
constIntA(4),
printIntA(1000),
receiveKeyboard(rosNodeHandler),

timedomain("Main time domain", dt, true)

{
		
	// Connect Blocks
	printIntA.getIn().connect(constIntA.getOut());
			
	
	// Run blocks
	timedomain.addBlock(&constIntA);
	timedomain.addBlock(&printIntA);
	timedomain.addBlock(&receiveKeyboard);
// 				
	eeros::task::Periodic td("control system",dt, timedomain);	
	eeros::Executor::instance().add(td);
}
	
