#include "MyFilter.hpp"

using namespace eeros;
using namespace eeros::control;



// MyFilter::MyFilter() : index(0) { }
MyFilter::MyFilter(double k) : k(k) { }

MyFilter::~MyFilter() { 
	// nothing to do...
}


void MyFilter::run() {
// 	prev[index] = in.getSignal().getValue();
// 	
// 	double sum = 0;
// 	
// 	for(int count=0; count < myFilterLength; count++) {
// 	  sum += prev[count];
// 	}
// 	
// 	index = (index+1)%myFilterLength;
// 	
// 	out.getSignal().setValue(sum/myFilterLength);
// 	out.getSignal().setTimestamp(in.getSignal().getTimestamp());
	
	

	double filtered; 
	
	filtered = prev * (1.0 - k) + in.getSignal().getValue() * k;
	prev = filtered;
	
	out.getSignal().setValue(filtered);
	out.getSignal().setTimestamp(in.getSignal().getTimestamp());
}
