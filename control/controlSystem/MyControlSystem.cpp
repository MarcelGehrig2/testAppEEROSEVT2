#include <math.h> 
#include <iomanip>

#include <eeros/core/Executor.hpp>
#include "MyControlSystem.hpp"

using namespace eeros::control;
using namespace std;


MyControlSystem::MyControlSystem(double dt, ros::NodeHandle& rosNodeHandler) :
// MyControlSystem::MyControlSystem(double dt) :
dt(dt),
rosNodeHandler(rosNodeHandler),

printDouble0(1),
printDouble1(1),
printDouble2(1),
// printBool0(1),
laserScanIn (rosNodeHandler, "/rosNodeTalker/TestTopic3", 100, false),
laserScanOut(rosNodeHandler, "/CSNodeTalker/TestTopic23", 100),
analogIn0("simpleRosIn0"),
// digitalIn0("batteryPresent0"),
// analogOut0("scanTimeEchoOut0"),
// digitalOut0("batteryPresentEchoOut0"),

// controler
// stepIn0(0,1,1),
motorPositionIn0("motorPositionIn0"),
// diffVel0(),
// pVel0(1),
// iVel0(0),
motorEffortOut0("motorEffortOut0"),


//Publisher for debuging
analogIn0Publisher(rosNodeHandler, "/debug/analogIn0", 100),
posToVel0Publisher(rosNodeHandler, "/debug/posToVel0", 100),
iwIntegrator0Publisher(rosNodeHandler, "/debug/iwIntegrator0", 100),
iwSum0Publisher(rosNodeHandler, "/debug/iwSum0", 100),

timedomain("Main time domain", dt, true)

{
	diffVel0.negateInput(1);
	pwGain0.setGain(16.5);
	iwGain0.setGain(32.5);
	iwIntegrator0.setInitCondition(0);
	iwIntegrator0.enable();
	kmGain0.setGain(0.0163);
	
	// Connect Blocks
// 	laserScanOut.getAngle_minInput().connect(laserScanIn.getAngle_minOutput());
// 	laserScanOut.getAngle_maxInput().connect(laserScanIn.getAngle_maxOutput());
// // 	laserScanOut.getIntensitiessInput().connect(laserScanIn.getIntensitiesOutput());
// 	laserScanOut.getIntensitiessInput().connect(laserScanIn.getRangesOutput());
// 	printDouble0.getIn().connect(analogIn0.getOut());
	posToVel0.getIn().connect(motorPositionIn0.getOut());
	diffVel0.getIn(0).connect(analogIn0.getOut());
	diffVel0.getIn(1).connect(posToVel0.getOut());
	
	pwGain0.getIn().connect(diffVel0.getOut());
	iwGain0.getIn().connect(diffVel0.getOut());
	iwIntegrator0.getIn().connect(iwGain0.getOut());
	iwSum0.getIn(0).connect(pwGain0.getOut());
	iwSum0.getIn(1).connect(iwIntegrator0.getOut());
	kmGain0.getIn().connect(iwSum0.getOut());
	
	printDouble0.getIn().connect(iwIntegrator0.getOut());
	printDouble1.getIn().connect(iwSum0.getOut());
	printDouble2.getIn().connect(kmGain0.getOut());
// 	printDouble2.getIn().connect(motorPositionIn0.getOut().getSignal().getTimestamp());
// 	printBool0.getIn().connect(digitalIn0.getOut());
// 	analogOut0.getIn().connect(analogIn0.getOut());
// 	digitalOut0.getIn().connect(digitalIn0.getOut());
// 	motorEffortOut0.getIn().connect(gain1.getOut());
// 	motorEffortOut0.getIn().connect(analogIn0.getOut());
	
// 	motorEffortOut0.getIn().connect(posToVel0.getOut());
	motorEffortOut0.getIn().connect(kmGain0.getOut());
	
	
	//Publisher for debuging
	analogIn0Publisher.getIn().connect(analogIn0.getOut());
	posToVel0Publisher.getIn().connect(posToVel0.getOut());
	iwIntegrator0Publisher.getIn().connect(iwIntegrator0.getOut());
	iwSum0Publisher.getIn().connect(iwSum0.getOut());
	

	// Run blocks
// 	timedomain.addBlock(&stepIn0);
	timedomain.addBlock(&motorPositionIn0);
	timedomain.addBlock(&analogIn0);
	
	timedomain.addBlock(&posToVel0);
	
	timedomain.addBlock(&diffVel0);
	timedomain.addBlock(&pwGain0);
	timedomain.addBlock(&iwGain0);
	timedomain.addBlock(&iwIntegrator0);
	timedomain.addBlock(&iwSum0);
	timedomain.addBlock(&kmGain0);
	
// // 	timedomain.addBlock(&laserScanIn);
// // 	timedomain.addBlock(&digitalIn0);
	timedomain.addBlock(&printDouble0);
	timedomain.addBlock(&printDouble1);
	timedomain.addBlock(&printDouble2);
// // 	timedomain.addBlock(&printBool0);
// // 	timedomain.addBlock(&analogOut0);
// // 	timedomain.addBlock(&digitalOut0);
	timedomain.addBlock(&motorEffortOut0);
	
	timedomain.addBlock(&analogIn0Publisher);
	timedomain.addBlock(&posToVel0Publisher);
	timedomain.addBlock(&iwIntegrator0Publisher);
	timedomain.addBlock(&iwSum0Publisher);
				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
