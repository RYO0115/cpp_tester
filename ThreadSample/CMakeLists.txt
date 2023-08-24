# Cmake version
cmake_minimum_required(VERSION 3.0)

# Project Name and Language
project(thread_sample CXX)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -pthread -std=c++11")
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
	./include
	)

link_directories(
	${PROJECT_SOURCE_DIR}
)

# Generate new_object_detection from main.cpp
#add_executable(new_object_detection src/main.cpp)
#add_library(point_type SHARED src/point_type.cpp)

#set(SDK_LIBRARY ${PROJECT_NAME}_static)
#install(TARGETS ${SDK_LIBRARY}
#        PUBLIC_HEADER DESTINATION include
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib)

#add_library(thread_sample STATIC src/thread_sample.cpp)

add_executable(thread_test test/thread_test.cpp
                            src/thread_sample.cpp
)
target_link_libraries( thread_test

)


