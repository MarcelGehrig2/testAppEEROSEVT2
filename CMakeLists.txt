cmake_minimum_required(VERSION 2.8)
 
project(testapptEEROSVT2)
 
find_package(EEROS REQUIRED)

## ucl++ workaround
## ////////////////////////////////////////////////////////////////////////
include_directories("/home/mgehrig2/VT2/Software/eeros-framework/buildx86/libucl-src/include")
link_directories("/home/mgehrig2/VT2/Software/eeros-framework/buildx86/libucl-build")


# ## ROS
# ## ////////////////////////////////////////////////////////////////////////
# include_directories("/opt/ros/kinetic/include")
# link_directories("/opt/ros/kinetic/lib")


## ROS without catkin
message( STATUS "ROS_ROOT: " $ENV{ROS_ROOT} )
message(STATUS "looking for package 'ROS'")
# http://wiki.ros.org/catkin/CMakeLists.txt#Include_Paths_and_Library_Paths
find_package( roslib REQUIRED )
if (roslib_FOUND)
	message( STATUS "-> ROS found")
	include_directories( "${roslib_INCLUDE_DIRS}" )
	message( STATUS "roslib_INCLUDE_DIRS: " ${roslib_INCLUDE_DIRS} )
	list(APPEND ROS_LIBRARIES "${roslib_LIBRARIES}")
	find_package( rosconsole REQUIRED)
	list(APPEND ROS_LIBRARIES "${rosconsole_LIBRARIES}")
	find_package( roscpp REQUIRED )
	list(APPEND ROS_LIBRARIES "${roscpp_LIBRARIES}")
else()
	message( STATUS "-> ROS NOT found")
endif()



include_directories(${EEROS_INCLUDE_DIR})
link_directories(${EEROS_LIB_DIR})

 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
add_executable(testappEEROSVT2
	main.cpp
	
	control/controlSystem/MyControlSystem.cpp

	
)




target_link_libraries(testappEEROSVT2 eeros ucl ${ROS_LIBRARIES})
