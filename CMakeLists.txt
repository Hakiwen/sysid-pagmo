cmake_minimum_required(VERSION 3.16)
project(sysid_pagmo)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build Examples" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_library(sysid_pagmo src/problem.cpp)

find_package(PAGMO REQUIRED)
message(STATUS "${PAGMO_INCLUDE_DIR}")
#message(STATUS "${PAGMO_LIBRARIES}")

find_package(Eigen3 REQUIRED)
message(STATUS "${EIGEN3_INCLUDE_DIR}")


include_directories( include ${PAGMO_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR})
target_link_libraries(sysid_pagmo ${PAGMO_LIBRARIES} )


if(BUILD_TESTS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
endif()

if(BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_SOURCE_DIR}/examples")
endif()