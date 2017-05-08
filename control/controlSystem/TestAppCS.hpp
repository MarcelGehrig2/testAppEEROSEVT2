#ifndef CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_
#define CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_


#include <eeros/control/TimeDomain.hpp> 

#include <eeros/control/Constant.hpp>
#include "Print.hpp"


using namespace eeros::control;

namespace testapptcpip {	
	
	class TestAppCS {		
	public:
		TestAppCS(double dt);
		
		std::string test = "test erfolgreich";
		
		// Define blocks
		Constant<int> constIntA;
		Print<int> printIntA;
		
		
// 		float maxPeriod[1000] = {0};
// 		static constexpr double dt = 0.01;
				
//	protected:
		double dt;
		bool realtime;
		eeros::control::TimeDomain timedomain;
	}; // END class
	
}; // END namespace

#endif // CH_NTB_TESTAPP_CONTROLSYSTEM_HPP_