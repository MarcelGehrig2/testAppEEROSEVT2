#ifndef ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_
#define ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_

#include <eeros/control/Block.hpp>
#include <eeros/control/Output.hpp>
#include <eeros/core/System.hpp>

#include <EcType.h>
#include <EcOs.h>

#include <iostream>

namespace testapptcpip {

		template < typename T = double >
		class GetEncoder: public eeros::control::Block {
			
		public:
			GetEncoder(EC_T_BYTE* pbyPDIn) : pbyPDIn(pbyPDIn) { }
			
			virtual void run() {
				output = EC_GET_FRM_DWORD( pbyPDIn + 2 );
				
				this->out.getSignal().setValue(output);
				this->out.getSignal().setTimestamp(eeros::System::getTimeNs());
			}
			
			virtual eeros::control::Output<T>& getOut() {
				return out;
			}

			eeros::control::Output<T> out;
			EC_T_BYTE* pbyPDIn;
			T output;
		};
	};
#endif /* ORG_EEROS_CONTROL_SEQUENCER_PROBE_HPP_ */
