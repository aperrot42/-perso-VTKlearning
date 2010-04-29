cmake_minimum_required(VERSION 2.6)

PROJECT(ITKVTKQT)

  # we want a debug version
  SET (CMAKE_BUILD_TYPE Debug)

  # We set a lot of flags to know what's going on
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
  SET(VTK_LIBRARIES vtkRendering vtkGraphics vtkHybrid
vtkImaging vtkIO vtkFiltering vtkCommon )

  #we use itk
  FIND_PACKAGE( ITK REQUIRED )
  INCLUDE( ${ITK_USE_FILE} )
  SET(ITK_LIBRARIES ITKBasicFilters ITKCommon ITKIO )

  # we use qt4
  FIND_PACKAGE( Qt4 REQUIRED )




  # sources of the project
  SET( ITKVTKQT_SRCS
       ItkVtkQt.cxx
       form.cxx
  )


  #We have several additional sources : the ItktoVtk wrappers
  # and some personal classes

  SET( SUBFOLDERS_LIST
    wrap
  )
  FOREACH( dir ${SUBFOLDERS_LIST} )
    ADD_SUBDIRECTORY( ${dir} )
    INCLUDE_DIRECTORIES( ${dir})
  ENDFOREACH( dir ${SUBFOLDERS_LIST} )



  # **********************QT SPECIFICS***************
  # Qt processed headers
  SET( ITKVTKQT_MOC_HDRS
      form.h
  )


  # Qt .ui files
  SET( ITKVTKQT_UIS
       form.ui
  )

  # Qt resource file
  #  SET( ITKVTKQT_RCS
  #       ./src/rc/sample.qrc
  #  )


  # enable warnings
  ADD_DEFINITIONS( -Wall )

  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
  SET( QT_USE_QT3SUPPORT FALSE )

  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
  INCLUDE( ${QT_USE_FILE} )

  # this command will generate rules that will run rcc on all files from SAMPLE_RCS
  # in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
  QT4_ADD_RESOURCES( ITKVTKQT_RC_SRCS ${ITKVTKQT_RCS} )

  # this will run uic on .ui files:
  QT4_WRAP_UI( ITKVTKQT_UI_HDRS ${ITKVTKQT_UIS} )

  # and finally this will run moc:
  QT4_WRAP_CPP( ITKVTKQT_MOC_SRCS ${ITKVTKQT_MOC_HDRS} )

  # we need this to be able to include headers produced by uic in our code
  # (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
  INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )


  #**************************************************




  # We finally build and link all together :
  ADD_EXECUTABLE(ItkVtkQt ${ITKVTKQT_SRCS} ${ITKVTKQT_MOC_SRCS} ${ITKVTKQT_RC_SRCS} ${ITKVTKQT_UI_HDRS})

  TARGET_LINK_LIBRARIES(ItkVtkQt ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${QT_LIBRARIES})



















