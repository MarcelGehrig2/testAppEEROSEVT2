#ifndef ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_
#define ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_

#include <eeros/control/Block.hpp>
#include <eeros/control/Input.hpp>
#include <eeros/core/System.hpp>

#include <iostream>

namespace testapptcpip {

		template < typename T = double >
		class SequencerProbe: public eeros::control::Block {
			
		public:
			SequencerProbe() : first(true), dataViable(false), firstValueChangedSinceLastCall(true), runCounter(0) { }
			
			virtual void run() {
				runCounter++;
				prevSignal = actSignal;
				actSignal = in.getSignal();
				if( first ) {
					first = false;
					dataViable = true;
				}
// 				else {
// 					// Ganz schlecht:
// // 					timestamp_t tin = this->in.getSignal().getTimestamp() / 1000000000.0;
// // 					timestamp_t tprev = this->prev.getTimestamp() / 1000000000.0;
// // 					double dt = static_cast<double>(tin - tprev);
// 					
// 					// Kein Unterschied:
// // 					double tin = static_cast<double>(this->in.getSignal().getTimestamp() / 1000000000.0);
// // 					double tprev = static_cast<double>(this->prev.getTimestamp() / 1000000000.0);
// 					double tin = this->in.getSignal().getTimestamp() / 1000000000.0;
// 					double tprev = this->prev.getTimestamp() / 1000000000.0;
// 					
// 					double dt = (tin - tprev);
// // 					double dt = 0.002;
// 					T valin = this->in.getSignal().getValue();
// 					T valprev = this->prev.getValue();
// 					
// 					if(enabled /*&& enable_ext.getSignal().getValue()*/)
// 						output = valprev + valin * dt;
// 					else
// 						output = valprev;
// 										
// 					this->out.getSignal().setValue(output);
// 					this->out.getSignal().setTimestamp(this->in.getSignal().getTimestamp());
// // 					this->out.getSignal().setTimestamp((this->in.getSignal().getTimestamp() + this->prev.getTimestamp()) / 2);
// 					this->prev = this->out.getSignal();
// 				}
			}

			eeros::control::Input<T>& getIn() 
			{
				return in;
			}
			
			eeros::control::Signal<T>& getActSignal() const
			{
				return actSignal;
			}
			
			eeros::control::Signal<T>& getPrevSignal() const
			{
				return prevSignal;
			}
			
			T getActValue() const
			{
				return actSignal.getValue();
			}
			
			T getPrevValue() const
			{
				return prevSignal.getValue();
			}
			
			bool valueChangedSinceLastCall() const
			{
				bool changed = false;
				if( firstValueChangedSinceLastCall ) {
					changed = false;
					firstValueChangedSinceLastCall = false;
				} 
				else {
					if( valueLastCall == actSignal.getValue() ) changed = false;
					else changed = true;	//also true for first call
				}
				valueLastCall = actSignal.getValue();
				return changed;
			}
			
			int runCounter;
			
		protected:
			bool first;
			bool dataViable;
			
			eeros::control::Input<T> in;
			eeros::control::Signal<T> actSignal;
			eeros::control::Signal<T> prevSignal;
			T valueLastCall;
			bool firstValueChangedSinceLastCall;
			
		};
	};
#endif /* ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_ */
