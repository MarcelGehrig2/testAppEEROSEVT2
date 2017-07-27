#ifndef ORG_EEROS_CONTROL_MY_STEP_HPP_
#define ORG_EEROS_CONTROL_MY_STEP_HPP_

#include <eeros/control/Block1i.hpp>
#include <eeros/core/System.hpp>

#include <iostream>

template < typename T = double >
class Print : public eeros::control::Block1i<T> {
		
	public:
		Print(int modulo=1) : modulo(modulo), counter(0) { }
		
		
		virtual void run() {
			if ( (counter % modulo) == 0 ) {
				std::cout << this->in.getSignal().getValue() << std::endl;
			}
			
			counter++;
		}
		
		
		int modulo;
		uint64_t counter;
};

#endif /* ORG_EEROS_CONTROL_MY_STEP_HPP_ */
