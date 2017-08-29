#ifndef DISCRET_HPP_
#define DISCRET_HPP_

#include <eeros/control/Block1i1o.hpp>


#include <stdlib.h>
#include <math.h>


class Discret: public eeros::control::Block1i1o<double> {
	
public:
// 	MyFilter();
	Discret(double step) : step(step) {};
	virtual ~Discret() {};
	virtual void run() {
	  double inputVal = in.getSignal().getValue();
	  double mod = fmod(inputVal, step);
	  double outputVal;
	  if(mod > (step/2))	outputVal=(inputVal-mod+step);
	  else 			outputVal=(inputVal-mod);
	  this->out.getSignal().setValue(outputVal);
	  this->out.getSignal().setTimestamp(in.getSignal().getTimestamp());
	};
	
protected:
	double step;
};
#endif /* DISCRET_HPP_ */