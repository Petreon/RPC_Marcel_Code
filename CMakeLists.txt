cmake_minimum_required(VERSION 3.20)
project(RPC_MARCEL_CODE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Include directories
include_directories(headers headers/utils includes/Eigen)

# Find all header files
file(GLOB_RECURSE HEADERS "headers/*.hpp")

# Find all source files
file(GLOB_RECURSE SOURCES "sources/*.cpp")

# Exclude mainWork.cpp from the library sources
list(REMOVE_ITEM SOURCES "sources/mainWork.cpp")

# Create a library with all the common source files
add_library(rpc_lib STATIC ${SOURCES})

# Enable testing with CTest
enable_testing()

# Find all test files
file(GLOB_RECURSE TESTS "tests/*.cpp")

# Add a test for each test file
foreach(test_file ${TESTS})
    # Get the test name from the file name
    get_filename_component(test_name ${test_file} NAME_WE)
    
    # Add the test executable and link it to the library
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} rpc_lib)
    
    # Add the test to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Add the main executable and link it to the library
add_executable(${PROJECT_NAME} sources/mainWork.cpp)
target_link_libraries(${PROJECT_NAME} rpc_lib)
