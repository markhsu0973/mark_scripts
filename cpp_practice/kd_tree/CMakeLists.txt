cmake_minimum_required(VERSION 2.6)
project(kd_tree)
 
find_package(PCL 1.2 REQUIRED)
 
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
add_executable(kd_tree src/kd_tree.cpp)
 
target_link_libraries (kd_tree ${PCL_LIBRARIES})
 
install(TARGETS kd_tree RUNTIME DESTINATION bin)

