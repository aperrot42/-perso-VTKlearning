cmake_minimum_required(VERSION 2.6)

PROJECT(DisplayImg)

# we want a debug version
 SET (CMAKE_BUILD_TYPE Debug)


IF(CMAKE_COMPILER_IS_GNUCXX)
  SET( CMAKE_CXX_FLAGS
    "-Wno-deprecated -Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wunused -Wpointer-arith -Winvalid-pch -Wcast-align -Wdisabled-optimization -Woverloaded-virtual -Wshadow -Wwrite-strings -Wstrict-null-sentinel -funit-at-a-time"
)
  SET( CMAKE_C_FLAGS
    "-Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wunused -Wpointer-arith -Winvalid-pch -Wcast-align -Wdisabled-optimization -Wshadow -Wwrite-strings -funit-at-a-time"
)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# we use vtk
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})


ADD_EXECUTABLE(DisplayImg DisplayImg.cxx)

TARGET_LINK_LIBRARIES(DisplayImg vtkHybrid vtkWidgets )
