#ifndef CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
#define CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_
 
#include <eeros/safety/SafetyProperties.hpp>

using namespace eeros;
using namespace eeros::hal;
using namespace eeros::safety;

class MySafetyProperties : public SafetyProperties {
public:
	MySafetyProperties() : slOff("off") {	
		addLevel(slOff);
		setEntryLevel(slOff);
	}
	
	SafetyLevel slOff;
};
 
#endif //CH_NTB_TEST_TESTAPPSAFETYPROPERTIES_HPP_

