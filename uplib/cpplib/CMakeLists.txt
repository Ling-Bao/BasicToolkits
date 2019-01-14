cmake_minimum_required(VERSION 3.10)
project(cpplib)
set(COLMAP_VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


################################################################################
# Include CMake dependencies
################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Include helper macros and commands, and allow the included file to override
# the CMake policies in this file
include(${CMAKE_SOURCE_DIR}/cmake/CMakeHelper.cmake NO_POLICY_SCOPE)


################################################################################
# Options
################################################################################

option(OPENMP_ENABLED "Whether to enable OpenMP" ON)
option(DEBUG "ON for debug or OFF for release" OFF)
option(CUDA_ENABLED "Whether to enable CUDA, if available" OFF)

if (DEBUG)
    add_definitions(-DDEBUG)
endif ()


################################################################################
# Find packages
################################################################################

if (OPENMP_ENABLED)
    find_package(OpenMP QUIET)
endif ()

find_package(Boost COMPONENTS
        program_options
        filesystem
        regex
        system
        unit_test_framework
        REQUIRED)

find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Glew REQUIRED)
find_package(OpenCV 3.4 REQUIRED)

set(CUDA_MIN_VERSION "7.0")
if (CUDA_ENABLED)
    find_package(CUDA ${CUDA_MIN_VERSION} QUIET)
endif ()

find_package(Qt5 REQUIRED)


################################################################################
# Compiler specific configuration
################################################################################

if (OPENMP_ENABLED AND OPENMP_FOUND)
    message(STATUS "Enabling OpenMP support")
    add_definitions("-DOPENMP_ENABLED")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else ()
    message(STATUS "Disabling OpenMP support")
endif ()

if (CUDA_FOUND)
    if (CUDA_ENABLED)
        add_definitions("-DCUDA_ENABLED")
        message(STATUS "Enabling CUDA support (version ${CUDA_VERSION_STRING})")
    else ()
        set(CUDA_FOUND FALSE)
        message(STATUS "Disabling CUDA support")
    endif ()
else ()
    set(CUDA_ENABLED FALSE)
    if (CUDA_VERSION_STRING)
        message(STATUS "Disabling CUDA support")
    else ()
        message(STATUS "Disabling CUDA support (found version "
                "${CUDA_VERSION_STRING} but >= ${CUDA_MIN_VERSION} required)")
    endif ()
endif ()

list(APPEND CUDA_NVCC_FLAGS "-Wno-deprecated-gpu-targets")
if (CUDA_ENABLED AND NOT IS_DEBUG)
    # Configure the NVCC flags:
    #   CUDA >= 5.0 <6.5:
    #     SASS:   sm_20, sm_30, sm_35
    #     PTX:    compute_35
    #   CUDA == 6.5:
    #     SASS:   sm_20, sm_30, sm_35, sm_37 sm_50
    #     PTX:    compute_50
    #   CUDA >= 7.0
    #     SASS:   sm_20, sm_30, sm_35, sm_37, sm_50, sm_52
    #     PTX:    compute_52
    #   CUDA >= 8.0
    #     SASS:   sm_20, sm_30, sm_35, sm_37, sm_50, sm_52, sm_60, sm_61
    #     PTX:    compute_60, compute_61

    # Add flags to generate SASS code.

    list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_20,code=sm_20")
    list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_30,code=sm_30")
    list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_35,code=sm_35")

    if (NOT CUDA_VERSION VERSION_LESS "6.5") # >= 6.5
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_37,code=sm_37")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_50,code=sm_50")
    endif ()

    if (NOT CUDA_VERSION VERSION_LESS "7.0") # >= 7.0
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_52,code=sm_52")
    endif ()

    if (NOT CUDA_VERSION VERSION_LESS "8.0") # >= 8.0
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_60,code=sm_60")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_61,code=sm_61")
    endif ()

    # Add flags to generate PTX code.
    if (CUDA_VERSION VERSION_LESS "6.5")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_35,code=compute_35")
    elseif (CUDA_VERSION VERSION_LESS "7.0")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_50,code=compute_50")
    elseif (CUDA_VERSION VERSION_LESS "8.0")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_52,code=compute_52")
    else () # >= 8.0
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_60,code=compute_60")
        list(APPEND CUDA_NVCC_FLAGS "-gencode;arch=compute_61,code=compute_61")
    endif ()
endif ()

# Qt5 was built with -reduce-relocations.
if (Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()


################################################################################
# Add sources
################################################################################

add_subdirectory(src)