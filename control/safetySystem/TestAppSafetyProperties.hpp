

#ifndef CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
#define CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
 
#include <eeros/safety/SafetyProperties.hpp>
//#include <eeros/hal/PeripheralOutput.hpp>
//#include <eeros/hal/PeripheralInput.hpp>
//#include <eeros/hal/ScalablePeripheralInput.hpp>
 
namespace testapptcpip {
 
    class TestAppCS;
 
    // ***** Define events ***** //
    enum {
	// e.g. doPowerUp = 1,
    };
 
    // ***** Define levels ***** //
    enum {
	// e.g. off = 1,
    };
 
    class TestAppSafetyProperties : public eeros::safety::SafetyProperties {
 
    public: 
	TestAppSafetyProperties(TestAppCS* cs);
// 	TestAppSafetyProperties();
	virtual ~TestAppSafetyProperties();
 
	// ***** Define critical outputs ***** //
 	// e.g. eeros::hal::PeripheralOutput<bool>* watchdog;
 
	// ***** Define critical inputs ***** //
 	//e.g. eeros::hal::PeripheralInput<bool>* emergencyButton;
 
	eeros::safety::SafetyLevel off;
	
    private:
	TestAppCS* controlSys;
 
    }; // end class
};     // end namespace
 
#endif //CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_

