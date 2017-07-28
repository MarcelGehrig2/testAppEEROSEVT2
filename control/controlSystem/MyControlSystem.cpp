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
printBool0(1),
laserScanIn (rosNodeHandler, "/rosNodeTalker/TestTopic3", 100, false),
laserScanOut(rosNodeHandler, "/CSNodeTalker/TestTopic23", 100),
// analogIn0("simpleRosIn0"),
analogIn0("scanTimeIn0"),
digitalIn0("batteryPresent0"),
analogOut0("scanTimeEchoOut0"),
digitalOut0("batteryPresentEchoOut0"),

timedomain("Main time domain", dt, true)

{
	// Connect Blocks
	laserScanOut.getAngle_minInput().connect(laserScanIn.getAngle_minOutput());
	laserScanOut.getAngle_maxInput().connect(laserScanIn.getAngle_maxOutput());
// 	laserScanOut.getIntensitiessInput().connect(laserScanIn.getIntensitiesOutput());
	laserScanOut.getIntensitiessInput().connect(laserScanIn.getRangesOutput());
	printDouble0.getIn().connect(analogIn0.getOut());
	printBool0.getIn().connect(digitalIn0.getOut());
	analogOut0.getIn().connect(analogIn0.getOut());
	digitalOut0.getIn().connect(digitalIn0.getOut());

	// Run blocks
	timedomain.addBlock(&laserScanIn);
	timedomain.addBlock(&analogIn0);
	timedomain.addBlock(&digitalIn0);
	timedomain.addBlock(&printDouble0);
	timedomain.addBlock(&printBool0);
	timedomain.addBlock(&analogOut0);
	timedomain.addBlock(&digitalOut0);
	timedomain.addBlock(&laserScanOut);
				
	eeros::task::Periodic td("control system",dt, timedomain);
	eeros::Executor::instance().add(td);
}
	
