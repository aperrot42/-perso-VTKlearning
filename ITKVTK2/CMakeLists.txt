cmake_minimum_required(VERSION 2.6)

PROJECT(ItkVtk2)

# we want a debug version
 SET (CMAKE_BUILD_TYPE Debug)

SET(ITK_LIBRARIES ITKBasicFilters ITKCommon ITKIO )

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



#we use itk
FIND_PACKAGE(ITK REQUIRED)
INCLUDE( ${ITK_USE_FILE} )


#We have several additional sources : the ItktoVtk wrappers
# and some personal classes
SET( SUBFOLDERS_LIST
  wrap
)
FOREACH( dir ${SUBFOLDERS_LIST} )
  ADD_SUBDIRECTORY( ${dir} )
  INCLUDE_DIRECTORIES( ${dir})
ENDFOREACH( dir ${SUBFOLDERS_LIST} )



ADD_EXECUTABLE(ItkVtk ItkVtk.cxx)

TARGET_LINK_LIBRARIES(ItkVtk ITKBasicFilters ITKCommon ITKIO
vtkRendering vtkGraphics vtkHybrid
vtkImaging vtkIO vtkFiltering vtkCommon )
