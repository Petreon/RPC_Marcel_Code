cmake_minimum_required(VERSION 3.20)
project(RPC_MARCEL_CODE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE)

#include directories

include_directories(headers headers/utils includes/Eigen)

#set(HEADERS
#     headers/mainWork.hpp
#    headers/Affine.hpp
#    headers/Deriv_B.hpp
#    headers/Deriv_H.hpp
#    headers/Deriv_L.hpp
#    #headers/img2terrain.hpp
 #   headers/latlong2utm.hpp
  #  headers/mmq.hpp
   # headers/Nor.hpp
   # headers/Polrfm.hpp
   # headers/RecalcRPC.hpp
   # headers/utils/RandPerm.hpp)

set(SOURCES
    sources/Affine.cpp
    sources/Deriv_B.cpp
    sources/Deriv_H.cpp
    sources/Deriv_L.cpp
    sources/img2terrain.cpp
    sources/latlong2utm.cpp
    sources/Lms.cpp
    sources/Desnor.cpp
    sources/Nor.cpp
    sources/Polrfm.cpp
    sources/RecalcRPC.cpp
    sources/utils/RandPerm.cpp
    sources/utils/MatrixSubSetting.cpp
    sources/utils/StandardDeviation.cpp
    )

add_executable(${PROJECT_NAME} sources/mainWork.cpp ${SOURCES} ${HEADERS})

#executable tests
#add_executable(MatrixSubSetting tests/MatrixSubSetting_tests.cpp ${SOURCES} ${HEADERS})
