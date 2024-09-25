cmake_minimum_required(VERSION 3.20)
project(RPC_MARCEL_CODE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include directories

include_directories(headers includes/Eigen)

set(SOURCES
    sources/mainWork.cpp
    sources/Affine.cpp
    sources/Deriv_B.cpp
    sources/Deriv_H.cpp
    sources/Deriv_L.cpp
    sources/img2terrain.cpp
    sources/latlong2utm.cpp
    sources/mmq.cpp
    sources/Nor.cpp
    sources/Polrfm.cpp
    sources/RecalcRPC.cpp
    sources/utils/RandPerm.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
