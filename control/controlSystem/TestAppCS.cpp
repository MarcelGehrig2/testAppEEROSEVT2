#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include <eeros/task/Periodic.hpp>

#include "TestAppCS.hpp"

using namespace testapptcpip;
using namespace eeros::control;
using namespace std;

TestAppCS::TestAppCS(double dt) : 
dt(dt),
	
constIntA(4),
printIntA(1000),

timedomain("Main time domain", dt, true)

{
		
	// Connect Blocks
	printIntA.getIn().connect(constIntA.getOut());
			
	
	// Run blocks
	timedomain.addBlock(&constIntA);
	timedomain.addBlock(&printIntA);
// 				
	eeros::task::Periodic td("control system",dt, timedomain);	
	eeros::Executor::instance().add(td);
}
	