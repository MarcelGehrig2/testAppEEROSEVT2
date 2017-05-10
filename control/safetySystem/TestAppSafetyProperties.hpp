#ifndef CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
#define CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
 
#include <eeros/safety/SafetyProperties.hpp>
//#include <eeros/hal/PeripheralOutput.hpp>
//#include <eeros/hal/PeripheralInput.hpp>
//#include <eeros/hal/ScalablePeripheralInput.hpp>

using namespace eeros;
using namespace eeros::hal;
using namespace eeros::safety;

namespace testapp {

	class TestAppCS;

	class TestAppSafetyProperties : public SafetyProperties {

		public:
		TestAppSafetyProperties(TestAppCS* cs);
		virtual ~TestAppSafetyProperties();

		SafetyLevel slOff;
		SafetyLevel slShuttingDown;
		SafetyLevel slIinitializing;
		SafetyLevel slInitialized;
		SafetyLevel slRunning;

		SafetyEvent seStartInitializing;
		SafetyEvent seStartRunning;
		SafetyEvent seShutDown;
		SafetyEvent seStopRunning;
		SafetyEvent seSwitchingOff;

		private:
		TestAppCS* controlSys;
		eeros::logger::Logger log;

		}; // end class
}     // end namespace
 
#endif //CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_

