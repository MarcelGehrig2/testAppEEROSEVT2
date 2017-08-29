#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include "MyControlSystem.hpp"

using namespace eeros::control;
using namespace std;


MyControlSystem::MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler) :
dt(dt),
rosNodeHandler(rosNodeHandler),
myFilter0(0.15),
// myFilter0(1),

printDouble0(1),
printDouble1(1),
printDouble2(1),
laserScanIn (rosNodeHandler, "/rosNodeTalker/TestTopic3", 100, false),
laserScanOut(rosNodeHandler, "/CSNodeTalker/TestTopic23", 100),
analogIn0("simpleRosIn0"),

discreterEncoder0(0.003141593),

// controller
motorPositionIn0("motorPositionIn0"),
motorEffortOut0("motorEffortOut0"),


//Publisher for debuging
motorPositionIn0Publisher(rosNodeHandler, "/debug/motorPositionIn0P", 100),
analogIn0Publisher(rosNodeHandler, "/debug/analogIn0", 100),
iwGain0Publisher(rosNodeHandler, "/debug/iwGain0", 100),
posToVel0Publisher(rosNodeHandler, "/debug/posToVel0", 100),
iwIntegrator0Publisher(rosNodeHandler, "/debug/iwIntegrator0", 100),
iwSum0Publisher(rosNodeHandler, "/debug/iwSum0", 100),
kmGain0Publisher(rosNodeHandler, "/debug/kmGain0", 100),

timedomain("Main time domain", dt, true)

{
	motorPositionIn0Fake.setValue(0.0163);
	diffVel0.negateInput(1);
	pwGain0.setGain(16.5);
// 	pwGain0.setGain(1.65);
	iwGain0.setGain(32.5);
	iwIntegrator0.setInitCondition(0);
	iwIntegrator0.enable();
	kmGain0.setGain(0.0163);
// 	kmGain0.setGain(1);
	
	// Connect Blocks
	discreterEncoder0.getIn().connect(motorPositionIn0.getOut());
// 	posToVel0.getIn().connect(motorPositionIn0.getOut());
	posToVel0.getIn().connect(discreterEncoder0.getOut());
// 	posToVel0.getIn().connect(motorPositionIn0Fake.getOut());
	myFilter0.getIn().connect(posToVel0.getOut());
// 	diffVel0.getIn(1).connect(posToVel0.getOut());
	diffVel0.getIn(1).connect(myFilter0.getOut());
	diffVel0.getIn(0).connect(analogIn0.getOut());
	
	  // controller
	pwGain0.getIn().connect(diffVel0.getOut());
	iwIntegrator0.getIn().connect(diffVel0.getOut());
	iwGain0.getIn().connect(iwIntegrator0.getOut());
	iwSum0.getIn(0).connect(pwGain0.getOut());
	iwSum0.getIn(1).connect(iwGain0.getOut());
	kmGain0.getIn().connect(iwSum0.getOut());
	
	  // output
	motorEffortOut0.getIn().connect(kmGain0.getOut());
// 	motorEffortOut0.getIn().connect(motorPositionIn0Fake.getOut());
	
	  // debugging std::cout
// 	printDouble0.getIn().connect(motorPositionIn0.getOut());
// 	printDouble0.getIn().connect(discreterEncoder0.getOut());
// 	printDouble1.getIn().connect(analogIn0.getOut());
// 	printDouble2.getIn().connect(kmGain0.getOut());
	printDouble0.getIn().connect(posToVel0.getOut());
	printDouble1.getIn().connect(myFilter0.getOut());
	printDouble2.getIn().connect(diffVel0.getOut());
	
	  // debugging ros topic
// 	motorPositionIn0Publisher.getIn().connect(motorPositionIn0.getOut());
	motorPositionIn0Publisher.getIn().connect(discreterEncoder0.getOut());
// // 	motorPositionIn0Publisher.getIn().connect(motorPositionIn0Fake.getOut());
	analogIn0Publisher.getIn().connect(analogIn0.getOut());
	iwGain0Publisher.getIn().connect(iwGain0.getOut());
	posToVel0Publisher.getIn().connect(posToVel0.getOut());
	iwIntegrator0Publisher.getIn().connect(myFilter0.getOut());
	iwSum0Publisher.getIn().connect(diffVel0.getOut());
	kmGain0Publisher.getIn().connect(kmGain0.getOut());
	

	// Run blocks
	  // inputs
// 	timedomain.addBlock(&motorPositionIn0Fake);
	timedomain.addBlock(&motorPositionIn0);
	timedomain.addBlock(&discreterEncoder0);
	timedomain.addBlock(&analogIn0);
	
	timedomain.addBlock(&posToVel0);
	timedomain.addBlock(&myFilter0);
	
	  // controller
	timedomain.addBlock(&diffVel0);
	timedomain.addBlock(&iwIntegrator0);
	timedomain.addBlock(&iwGain0);
	timedomain.addBlock(&pwGain0);
	timedomain.addBlock(&iwSum0);
	timedomain.addBlock(&kmGain0);
	
	  // debugging std::cout
	timedomain.addBlock(&printDouble0);
	timedomain.addBlock(&printDouble1);
	timedomain.addBlock(&printDouble2);
	
	  // debugging ros topic
	timedomain.addBlock(&motorPositionIn0Publisher);
	timedomain.addBlock(&analogIn0Publisher);
	timedomain.addBlock(&posToVel0Publisher);
	timedomain.addBlock(&iwGain0Publisher);
	timedomain.addBlock(&iwIntegrator0Publisher);
	timedomain.addBlock(&iwSum0Publisher);
	timedomain.addBlock(&kmGain0Publisher);
	
	  // output
	timedomain.addBlock(&motorEffortOut0);
				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
