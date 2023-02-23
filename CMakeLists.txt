cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged

project(partitioner)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories("include/")

file(GLOB SOURCES "src/*.cc")

add_executable(__partitioner__ ${SOURCES})

