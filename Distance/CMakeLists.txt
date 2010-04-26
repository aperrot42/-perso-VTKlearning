cmake_minimum_required(VERSION 2.6)
 
PROJECT(Distance)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(Distance Distance.cxx)
