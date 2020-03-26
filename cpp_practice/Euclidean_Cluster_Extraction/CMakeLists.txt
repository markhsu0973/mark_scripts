cmake_minimum_required(VERSION 2.6)
project(Euclidean_Cluster_Extraction)
 
find_package(PCL 1.2 REQUIRED)
 
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
add_executable(Euclidean_Cluster_Extraction src/Euclidean_Cluster_Extraction.cpp)
 
target_link_libraries (Euclidean_Cluster_Extraction ${PCL_LIBRARIES})
 
install(TARGETS Euclidean_Cluster_Extraction RUNTIME DESTINATION bin)
