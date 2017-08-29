#ifndef ROSBLOCKPUBLISHER_SENSORMSGS_JOINTSTATE_HPP
#define ROSBLOCKPUBLISHER_SENSORMSGS_JOINTSTATE_HPP

#include <eeros/control/ROS/RosBlockPublisher.hpp>
#include <eeros/math/Matrix.hpp>

// A-1 Include the header file of the ROS message
#include <sensor_msgs/JointState.h>

using namespace eeros::control;



// C-1 Create the template definition. Each EEROS matrix input needs its own type
// template < typename TPositionsInput, typename TVelocitiesInput, typename TEffortsInput >

// A-3 Name your block and create the constructor. Copy the type definition
class RosBlockPublisher_SensorMsgs_JointState : public RosBlockPublisher< sensor_msgs::JointState::Type > {
	// A-2 Define the type of the ROS message
	typedef sensor_msgs::JointState::Type	TRosMsg;
	
	// temporary:
	typedef double TPositionsInput;
	typedef double TVelocitiesInput;
	typedef double TEffortsInput;
public:
	RosBlockPublisher_SensorMsgs_JointState(ros::NodeHandle& rosNodeHandler,
										   const std::string& topic,
										   const uint32_t queueSize=1000,
										   const std::string jointName=""
 					      ) :
		RosBlockPublisher< TRosMsg >( rosNodeHandler, topic, queueSize ),
		jointName(jointName)
		{}
		
	void setRosMsg(TRosMsg& msg) {
		// B-3 If available, set time in msg header
		msg.header.stamp = eeros::control::rosTools::convertToRosTime(eeros::System::getTimeNs());
		
		// B-4 Check if EEROS input is connected. Cast the data. Assign casted data to ROS message field
// 		auto value = positionsInput.getSignal().getValue();
		std::vector<double> positions;
		std::vector<double> velocities;
		std::vector<double> efforts;
		if (positionsInput.isConnected() ) {
			positions.push_back(positionsInput.getSignal().getValue());
			msg.position = positions;
		}
		if (velocitiesInput.isConnected() ) {
			velocities.push_back(velocitiesInput.getSignal().getValue());
			msg.position = velocities;
		}
		if (effortsInput.isConnected() ) {
			efforts.push_back(effortsInput.getSignal().getValue());
			msg.position = efforts;
		}
		
// 	  
// 		// C-4 Check if EEROS input is connected
// // 		if (positionsInput.isConnected() ) {
// // 			// C-5 Get the vector from the EEROS input
// // 			positionsValue = positionsInput.getSignal().getValue();
// // 			auto positionsTmpDouble = positionsValue.getColVector(0);
// // 			// C-6 Cast the vector and assign it to the appropriate ROS data field
// // 			std::vector<double> positionsTmpFloat( positionsTmpDouble.begin(), positionsTmpDouble.end() );	// cast to float vector
// // 			msg.position			= positionsTmpFloat;
// // 		}
// // 		if (velocitiesInput.isConnected() ) {
// // 			velocitiesValue = velocitiesInput.getSignal().getValue();
// // 			auto velocitiesTmpDouble = velocitiesValue.getColVector(0);
// // 			std::vector<double> velocitiesTmpFloat( velocitiesTmpDouble.begin(), velocitiesTmpDouble.end() );	// cast to float vector
// // 			msg.velocity			= velocitiesTmpFloat;
// // 		}
// // 		if (effortsInput.isConnected() ) {
// // 			effortsValue = effortsInput.getSignal().getValue();
// // 			auto effortsTmpDoubles = effortsValue.getColVector(0);
// // 			std::vector<double> effortsTmpFloat( effortsTmpDoubles.begin(), effortsTmpDoubles.end() );	// cast to float vector
// // 			msg.effort			= effortsTmpFloat;
// // 		}

		std::vector<std::string> names;
		names.push_back(jointName);
 		msg.name=names;
	}
	
	// B-2 Add a 'getInput()' function for each input
	
	// C-3 Add a 'getInput()' function for each EEROS matrix Input
	Input<TPositionsInput>& getPositionsInput()		{return positionsInput; };
	Input<TVelocitiesInput>& getVelocitiesInput()		{return velocitiesInput; };
	Input<TEffortsInput>& getEffortsInput()			{return effortsInput; };
		
protected:
	// B-1 Create EEROS inputs
  
	// C-2 Create a 'value' and an 'input' variable for each EEROS matrix input
	TPositionsInput				positionsValue;
	Input<TPositionsInput>			positionsInput;
	TVelocitiesInput			velocitiesValue;
	Input<TVelocitiesInput>			velocitiesInput;
	TEffortsInput				effortsValue;
	Input<TEffortsInput>			effortsInput;
	
	std::string 		jointName;
};


#endif // ROSBLOCKPUBLISHER_SENSORMSGS_JOINTSTATE_HPP