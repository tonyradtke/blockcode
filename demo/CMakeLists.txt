cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged

project(demo)

#
# set vars
#
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(LIB_NAME "partitioner")
SET(DEMO_BINARY "__demo__")
SET(INCLUDE_DIR "/usr/local/include")

#
#  wrangle files
#
include_directories("include/")
include_directories(${INCLUDE_DIR})

file(GLOB EXE_SOURCES "src/*.cc")

#
# link
#
add_executable(${DEMO_BINARY} ${EXE_SOURCES})



