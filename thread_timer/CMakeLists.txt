
# Cmake version
cmake_minimum_required(VERSION 3.0)

# Project Name and Language
project(udp_sample CXX)

set(CMAKE_CXX_FLAGS "-O2 -Wall -pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# Add Subdirectory
#add_subdirectory(src)

# Add Include dir
#target_include_directories(
#	new_object_detection
#	${PROJECT_SOURCE_DIR}/include
#)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

link_directories(
	${PROJECT_SOURCE_DIR}
)


add_executable(timer_test test/timer_test.cpp)
target_link_libraries(timer_test
)


#add_library(simple_udp SHARED src/simple_udp.cpp)

# udp test code
#set(TEST_NAME "pub_udp")
#add_executable(${TEST_NAME} 
#	test/pub_udp.cpp
#   	)
#target_link_libraries(${TEST_NAME}
#	simple_udp
#)
#
#set(TEST_NAME "sub_udp")
#add_executable(${TEST_NAME} 
#	test/sub_udp.cpp
#   	)
#target_link_libraries(${TEST_NAME}
#	simple_udp
#)


