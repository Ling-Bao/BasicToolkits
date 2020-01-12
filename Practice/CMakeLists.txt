cmake_minimum_required(VERSION 2.8)
project(cpp_ws)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES
	src/binary_search.h
	src/find_k_node.h
	src/fibonacci.h)

add_executable(cpp_ws main.cpp ${SOURCE_FILES})