cmake_minimum_required(VERSION 2.8)
project(project)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")
include_directories("${CMAKE_SOURCE_DIR}")
add_library(practicalsocket PracticalSocket.cpp)
target_link_libraries (practicalsocket pthread rt)

set(SOURCE_FILES main.cpp app.cpp app.h)
add_executable(project ${SOURCE_FILES})
