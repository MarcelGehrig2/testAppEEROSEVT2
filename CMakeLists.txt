cmake_minimum_required(VERSION 2.8)
 
project(testapptVT2)
 
find_package(EEROS REQUIRED)

## ucl++ workaround
## ////////////////////////////////////////////////////////////////////////
include_directories("/home/mgehrig2/VT2/Software/eeros-framework/buildx86/libucl-src/include")
link_directories("/home/mgehrig2/VT2/Software/eeros-framework/buildx86/libucl-build")

include_directories(${EEROS_INCLUDE_DIR})
link_directories(${EEROS_LIB_DIR})
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
add_executable(testappVT2
	main.cpp
	
	control/controlSystem/TestAppCS.cpp
	control/safetySystem/TestAppSafetyProperties.cpp

	
)




target_link_libraries(testappVT2 eeros ucl)
