cmake_minimum_required(VERSION 3.20)
project(RPC_MARCEL_CODE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include directories

include_directories(headers includes/Eigen)

set(SOURCES
    sources/mainWork.cpp
    sources/Affine.cpp
    sources/Nor.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
