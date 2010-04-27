cmake_minimum_required(VERSION 2.6)

PROJECT(Objects)

# we want a debug version
SET (CMAKE_BUILD_TYPE Debug)

# we use vtk
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(objects objects.cxx)

TARGET_LINK_LIBRARIES(objects vtkHybrid)
