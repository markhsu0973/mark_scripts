cmake_minimum_required(VERSION 2.6)
project(read_pcd)
 
find_package(PCL 1.2 REQUIRED)
 
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
add_executable(read_pcd src/read_pcd.cpp)
 
target_link_libraries (read_pcd ${PCL_LIBRARIES})
 
install(TARGETS read_pcd RUNTIME DESTINATION bin)

