#ifndef MY_FILTER_HPP_
#define MY_FILTER_HPP_

#include <eeros/control/Block1i1o.hpp>


#include <stdlib.h>
#include <cmath>


class MyFilter: public eeros::control::Block1i1o<double> {
	
public:
// 	MyFilter();
	MyFilter(double k);
	virtual ~MyFilter();
	virtual void run();
	
protected:
	double k;
	double prev;
};
#endif /* MY_FILTER_HPP_ */