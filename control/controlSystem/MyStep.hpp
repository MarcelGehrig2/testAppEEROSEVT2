#ifndef ORG_EEROS_CONTROL_MY_STEP_HPP_
#define ORG_EEROS_CONTROL_MY_STEP_HPP_

#include <eeros/control/Block1o.hpp>
#include <eeros/core/System.hpp>

#include <chrono>

namespace testapptcpip {

	template < typename T = double >
	class MyStep : public eeros::control::Block1o<T> {
			using seconds = std::chrono::duration<double, std::chrono::seconds::period>;
			
		public:
			MyStep(T initValue = 0, T stepHeight = 1, double delayTime = 1) : delayTime(delayTime) {
				setInitValue(initValue);
				setStepHeight(stepHeight);
// 				this.delayTime = delayTime;
				stepDone=false;
				first=true;
			}
			
			
			virtual void run() {
				actTime = std::chrono::steady_clock::now();
// 				diff = stepTime - eeros::System::getTimeNs();
				if(first) {
					startTime = std::chrono::steady_clock::now();
// 					stepTime = std::chrono::steady_clock::now() + seconds(delayTime);
					this->out.getSignal().setValue(initValue);
					first = false;
				}
				else if(!stepDone && std::chrono::duration_cast<std::chrono::seconds>(actTime-startTime).count() >= delayTime) {
					this->out.getSignal().setValue(initValue + stepHeight);
					stepDone = true;
				}
				this->out.getSignal().setTimestamp(eeros::System::getTimeNs());
			}
			
			virtual void reset() {
				stepDone = false;
				first = true;
			}
			
			virtual void setInitValue(T initValue) {
				this->initValue = initValue;
			}
			
			virtual void setStepHeight(T stepHeight) {
				this->stepHeight = stepHeight;
			}
			
			virtual void setDelayTime(double delayTime) {
				this->stepTime = delayTime;
			}

			std::chrono::time_point<std::chrono::steady_clock> startTime;
			std::chrono::time_point<std::chrono::steady_clock> actTime;
			uint64_t diff;
// 		protected:
			T initValue;
			T stepHeight;
			uint64_t stepTime;
			double delayTime;
			bool stepDone;
			bool first;
		};

};

#endif /* ORG_EEROS_CONTROL_MY_STEP_HPP_ */
