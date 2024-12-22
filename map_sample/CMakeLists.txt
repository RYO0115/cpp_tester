# Cmake version
cmake_minimum_required(VERSION 3.5)

# Project Name and Language
project(sample_thread CXX)


set(CMAKE_CXX_FLAGS "-g -O0 -Wall -pthread -std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
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
	${PROJECT_SOURCE_DIR}/lib
)

#add_library(map_sample_class src/map_sample_class.cpp)


add_executable(map_test test/map_test.cpp
)
target_link_libraries( map_test
	#map_sample_class

)


