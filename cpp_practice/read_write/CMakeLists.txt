cmake_minimum_required (VERSION 2.6)

project (class)

# check c++11 / c++0x
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "-std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_executable (practice src/practice.cpp)
add_executable (HW7-4 src/HW7-4.cpp)
add_executable (HW7-5 src/HW7-5.cpp)
add_executable (HW8-1 src/HW8-1.cpp)
add_executable (HW8-2 src/HW8-2.cpp)


