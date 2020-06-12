cmake_minimum_required (VERSION 2.6)

project (serial)



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

add_executable (Serial_TX src/Serial_TX.cpp)
add_executable (Serial_RX src/Serial_RX.cpp)
add_executable (modbus_read_write src/modbus_read_write.cpp)
add_executable (serial_tx_rx src/serial_tx_rx.cpp)
add_executable (test src/test.cpp)
