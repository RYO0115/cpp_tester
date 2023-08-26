# Cmake version
cmake_minimum_required(VERSION 3.0)

# Project Name and Language
project(cpp_tester CXX)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)


# Add Subdirectory
#add_subdirectory(src)

# Add Include dir
#target_include_directories(
#	${PROJECT_SOURCE_DIR}/include
#)



# Generate new_object_detection from main.cpp
#add_executable(new_object_detection src/main.cpp)
add_subdirectory(udp_sample)
add_subdirectory(multi_threading)
#add_subdirectory(ThreadSample)
