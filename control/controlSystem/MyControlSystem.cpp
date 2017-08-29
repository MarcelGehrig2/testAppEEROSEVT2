#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include "MyControlSystem.hpp"

using namespace eeros::control;
using namespace std;


MyControlSystem::MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler) :
dt(dt),
rosNodeHandler(rosNodeHandler),
lowPassFilter(0.15),
// lowPassFilter(1),
iSaturation(-2.5,2.5),

printDouble0(1),
printDouble1(1),
printDouble2(1),
laserScanIn (rosNodeHandler, "/rosNodeTalker/TestTopic3", 100, false),
laserScanOut(rosNodeHandler, "/CSNodeTalker/TestTopic23", 100),
analogIn("simpleRosIn0"),

discreterEncoder(0.003141593),

// controller
motorPositionIn("motorPositionIn0"),
effortOut("motorEffortOut0"),


//Publisher for debuging
positionPublisher(rosNodeHandler, "/debug/position", 100),
veloctiyPublisher(rosNodeHandler, "/debug/velocity", 100),
velocityFilteredPublisher(rosNodeHandler, "/debug/velocityFiltered", 100),
iSetPublisher(rosNodeHandler, "/debug/iSet", 100),
debugPublisher0(rosNodeHandler, "/debug/debug0", 100),
debugPublisher1(rosNodeHandler, "/debug/debug1", 100),
debugPublisher2(rosNodeHandler, "/debug/debug2", 100),
jointStatePublisher(rosNodeHandler, "/motor/joint_states", 100,"motor_axis"),

timedomain("Main time domain", dt, true)

{
	motorPositionInFake.setValue(0.0163);
	diffVel.negateInput(1);
	pwGain.setGain(1.65);
// 	pwGain.setGain(16.5);
	iwGain.setGain(3.25);
// 	iwGain.setGain(32.5);
	iwIntegrator.setInitCondition(0);
	iwIntegrator.enable();
	kmGain.setGain(0.0163);
	
	// Connect Blocks
	discreterEncoder.getIn().connect(motorPositionIn.getOut());
	posToVel.getIn().connect(discreterEncoder.getOut());
	lowPassFilter.getIn().connect(posToVel.getOut());
	diffVel.getIn(1).connect(lowPassFilter.getOut());
	diffVel.getIn(0).connect(analogIn.getOut());
	
	  // controller
	pwGain.getIn().connect(diffVel.getOut());
	iwIntegrator.getIn().connect(diffVel.getOut());
	iwGain.getIn().connect(iwIntegrator.getOut());
	iSum.getIn(0).connect(pwGain.getOut());
	iSum.getIn(1).connect(iwGain.getOut());
	iSaturation.getIn().connect(iSum.getOut());
	kmGain.getIn().connect(iSaturation.getOut());
	
	  // output
	effortOut.getIn().connect(kmGain.getOut());
// 	effortOut.getIn().connect(motorPositionInFake.getOut());
	
	  // debugging std::cout
	
	  // debugging ros topic
	positionPublisher.getIn().connect(discreterEncoder.getOut());
	veloctiyPublisher.getIn().connect(posToVel.getOut());
	velocityFilteredPublisher.getIn().connect(lowPassFilter.getOut());
	iSetPublisher.getIn().connect(iSaturation.getOut());
	debugPublisher0.getIn().connect(analogIn.getOut());
// 	debugPublisher1.getIn().connect(lowPassFilter.getOut());
// 	debugPublisher2.getIn().connect(diffVel.getOut());
	jointStatePublisher.getPositionsInput().connect(discreterEncoder.getOut());

	// Run blocks
	  // inputs
// 	timedomain.addBlock(motorPositionInFake);
	timedomain.addBlock(motorPositionIn);
	timedomain.addBlock(discreterEncoder);
	timedomain.addBlock(analogIn);
	
	timedomain.addBlock(posToVel);
	timedomain.addBlock(lowPassFilter);
	
	  // controller
	timedomain.addBlock(diffVel);
	timedomain.addBlock(iwIntegrator);
	timedomain.addBlock(iwGain);
	timedomain.addBlock(pwGain);
	timedomain.addBlock(iSum);
	timedomain.addBlock(iSaturation);
	timedomain.addBlock(kmGain);
	
	  // debugging std::cout
// 	timedomain.addBlock(printDouble0);
// 	timedomain.addBlock(printDouble1);
// 	timedomain.addBlock(printDouble2);
	
	  // debugging ros tpic
	timedomain.addBlock(positionPublisher);
	timedomain.addBlock(veloctiyPublisher);
	timedomain.addBlock(velocityFilteredPublisher);
	timedomain.addBlock(iSetPublisher);
	timedomain.addBlock(debugPublisher0);
// 	timedomain.addBlock(debugPublisher1);
// 	timedomain.addBlock(debugPublisher2);
	timedomain.addBlock(jointStatePublisher);
	
	  // output
	timedomain.addBlock(effortOut);
				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
