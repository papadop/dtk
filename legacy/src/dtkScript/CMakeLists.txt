### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2009 - Julien Wintz, Inria.
## Created: Tue Mar 10 15:12:38 2009 (+0100)
## Version: $Id$
## Last-Updated: Thu Jan 10 11:33:06 2013 (+0100)
##           By: Julien Wintz
##     Update #: 102
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkScript)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkScriptInterpreter.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkScriptInterpreter.h)

set(${PROJECT_NAME}_SOURCES
  dtkScriptInterpreter.cpp)

if(DTK_BUILD_WRAPPERS AND DTK_HAVE_PYTHON)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkScriptInterpreterPython.h)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkScriptInterpreterPython.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkScriptInterpreterPython.cpp)

endif(DTK_BUILD_WRAPPERS AND DTK_HAVE_PYTHON)

if(DTK_BUILD_WRAPPERS AND DTK_HAVE_TCL)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkScriptInterpreterTcl.cpp)

endif(DTK_BUILD_WRAPPERS AND DTK_HAVE_TCL)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  dtkCore
  dtkLog)

if(DTK_BUILD_WRAPPERS AND DTK_HAVE_TCL)

target_link_libraries(${PROJECT_NAME} ${TCL_LIBRARY})

endif(DTK_BUILD_WRAPPERS AND DTK_HAVE_TCL)

if(DTK_BUILD_WRAPPERS AND DTK_HAVE_PYTHON)

target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})

endif(DTK_BUILD_WRAPPERS AND DTK_HAVE_PYTHON)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_UIC} ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h")

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

