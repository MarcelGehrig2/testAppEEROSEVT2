#include "MyFilter.hpp"

using namespace eeros;
using namespace eeros::control;



MyFilter::MyFilter(double k) : k(k), prev(0) { }

MyFilter::~MyFilter() { 
	// nothing to do...
}


void MyFilter::run() {
	

	double filtered; 
	
	filtered = prev * (1.0 - k) + in.getSignal().getValue() * k;
	prev = filtered;
	
	out.getSignal().setValue(filtered);
	out.getSignal().setTimestamp(in.getSignal().getTimestamp());
}
