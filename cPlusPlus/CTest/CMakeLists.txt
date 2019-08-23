cmake_minimum_required(VERSION 3.13)
project(ctest)

set(CMAKE_CXX_STANDARD 14)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-O3" )

# Set output directories for libraries and executables
SET(BASE_DIR ${CMAKE_SOURCE_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BASE_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BASE_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin)

# 添加Eigen头文件
include_directories( "/home/bl/workspace/libs/include/eigen3/" )

add_subdirectory(useEigen)

add_executable(ctest main.cpp)