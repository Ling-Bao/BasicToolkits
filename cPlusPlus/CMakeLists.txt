cmake_minimum_required(VERSION 3.5)
project(cPlusPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp "SortAlgorithm/SortSelf.h" "SortAlgorithm/SortCommonHeader.h" ToolsSelf/SortTools.h)
add_executable(cPlusPlus ${SOURCE_FILES})