#ifndef ORG_EEROS_CONTROL_FILTER_LOW_PASS_HPP_
#define ORG_EEROS_CONTROL_FILTER_LOW_PASS_HPP_

#include <eeros/control/Block1i1o.hpp>
#include <eeros/core/System.hpp>

#include <array>

using namespace eeros::control;

template < typename T = double >
class FilterLowPass : public eeros::control::Block1i1o<T> {
public:
	FilterLowPass() : pointerToNewestElement(0) {
		for(int i=0; i<lengthOfFilter; i++) {
			values[i] = 0;
		}
	}
	
	virtual void run() {
		values[pointerToNewestElement] = this->in.getSignal().getValue();
		mean = 0;
		for(int i=0; i<lengthOfFilter; i++) {
			mean += values[i];
		}
		mean = mean/lengthOfFilter;
// 			actTime = std::chrono::steady_clock::now();
// // 				diff = stepTime - eeros::System::getTimeNs();
// 			if(first) {
// 				startTime = std::chrono::steady_clock::now();
// // 					stepTime = std::chrono::steady_clock::now() + seconds(delayTime);
// 				this->out.getSignal().setValue(initValue);
// 				first = false;
// 			}
// 			else if(!stepDone && std::chrono::duration_cast<std::chrono::seconds>(actTime-startTime).count() >= delayTime) {
// 				this->out.getSignal().setValue(initValue + stepHeight);
// 				stepDone = true;
// 			}
		this->out.getSignal().setValue(mean);
		this->out.getSignal().setTimestamp(this->in.getSignal().getTimestamp());
		pointerToNewestElement = (pointerToNewestElement+1)%lengthOfFilter;
	}
	
// 	static constexpr std::array<double, 3>
// 	static constexpr lengthOfFilter = 5;
// 	static
	T mean;
	int pointerToNewestElement;
	static constexpr int lengthOfFilter = 10;
	std::array<T, lengthOfFilter> values;
};



#endif /* ORG_EEROS_CONTROL_FILTER_LOW_PASS_HPP_ */
