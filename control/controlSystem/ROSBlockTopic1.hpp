#ifndef ROSBLOCKTOPIC1_HPP
#define ROSBLOCKTOPIC1_HPP

#include <ros/ros.h>
#include <eeros/control/Block.hpp>
#include <eeros/control/Output.hpp>
#include <eeros/core/System.hpp>

// includes used for ROS message types
#include <std_msgs/Float64.h>
//#include <sensor_msgs/Joy.h>
//#include <sensor_msgs/LaserScan.h>


namespace testapp {
	class ROSBlockTopic1 : public eeros::control::Block {

		// USER DEFINED: Adapt the type definitions for your application.
		//               Multiple outputs are possible.
		//               It is not easily possible, to subscribe to multiple ROS topics with one block
		typedef std_msgs::Float64::Type		typeROSMessage;		// Depends on ROS topic
		typedef double						typeOutput;			// Depends on desired block output
		// END OF USER DEFINED

	public:
		ROSBlockTopic1(ros::NodeHandle& rosNodeHandler, const std::string& topic, uint32_t queueSize=1000) :
		rosNodeHandler(rosNodeHandler),
		topic (topic)
		{
			out.getSignal().clear();	//clear EEROS signal

			subscriber = rosNodeHandler.subscribe(topic, queueSize, &ROSBlockTopic1::rosCallbackFct, this);
			ROS_DEBUG_STREAM("ROSBlock, reading from topic: '" << topic << "' created.");
		}


		virtual void rosCallbackFct(const typeROSMessage& msg) {

			out.getSignal().setTimestamp(eeros::System::getTimeNs());

			// USER DEFINED: 1.) Get the data from the message
			//               2.) Cast the data if necessary
			//               3.) Insert the data in the output signal
			outValue = static_cast<typeOutput>( msg.data );		// depends heavily ond the type of the ROS message
			out.getSignal().setValue( outValue );
			// END OF USER DEFINED
		}


		virtual void run() {
			ros::spinOnce();	//every run, ROS checks, if there is a new message on subscribed topic
		}


		virtual eeros::control::Output<typeOutput>& getOut() {
			return out;
		}


	protected:
		eeros::control::Output<typeOutput> out;
		typeOutput outValue;

		//ROS variables
		ros::NodeHandle& rosNodeHandler;
		ros::Subscriber subscriber;
		const std::string& topic;

	private:
//			template <typename S> typename std::enable_if<std::is_arithmetic<S>::value>::type _clear() {
//				value = std::numeric_limits<double>::quiet_NaN();
//			}

//			template <typename S> typename std::enable_if<!std::is_arithmetic<S>::value>::type _clear() {
//				value.fill(std::numeric_limits<double>::quiet_NaN());
//			}
	};

//		/********** Print functions **********/
//		template <typename T>
//		std::ostream& operator<<(std::ostream& os, ROSBlock<T>& c) {
//			os << "ROSBlockTopic1: '" << c.getName() << "' init val = " << c.value;
//		}
};


#endif // ROSBLOCKTOPIC1_HPP
