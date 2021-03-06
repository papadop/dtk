### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:30:43 2009 (+0200)
## Version: $Id$
## Last-Updated: jeu. nov. 28 22:52:33 2013 (+0100)
##           By: Nicolas Niclausse
##     Update #: 402
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

cmake_minimum_required(VERSION 2.8.6)

project(dtk)

set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "dtk major version number." FORCE)
set(${PROJECT_NAME}_VERSION_MINOR 6 CACHE STRING "dtk minor version number." FORCE)
set(${PROJECT_NAME}_VERSION_BUILD 1 CACHE STRING "dtk build version number." FORCE)
set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include("GNUInstallDirs")

option(BUILD_SHARED_LIBS       "Build shared libraries"  true)
option(DTK_BUILD_TOOLS         "Build tools"             true)
option(DTK_BUILD_EXAMPLES      "Build examples"          false)
option(DTK_BUILD_TESTING       "Build testing"           false)
option(DTK_BUILD_DOCUMENTATION "Build documentation"     false)
option(DTK_BUILD_WRAPPERS      "Build wrappers"          false)
option(DTK_BUILD_REPORTING     "Build reporting"         false)
option(DTK_BUILD_TUTORIALS     "Build tutorials"         false)
option(DTK_BUILD_MPI           "Build mpi related code"  false)
option(DTK_BUILD_VIDEO         "Build video related code" false)

option(DTK_BUILD_DISTRIBUTED   "Build distributed layer" true)
option(DTK_BUILD_COMPOSER      "Build composer layer"    true)
option(DTK_BUILD_ZIP           "Build zip layer"         true)
option(DTK_BUILD_VR            "Build vr layer"          true)
option(DTK_BUILD_PLOT          "Build plotting layer"    true)
option(DTK_BUILD_SCRIPT        "Build scripting layer"   true)

if(MSVC)
  option(DTK_USE_PRECOMPILED_HEADERS "Use precompiled headers" true)
endif(MSVC)

include(dtkDependencies)
include(dtkBuild)
include(dtkPack)
include(dtkPch)

add_subdirectory(include)
add_subdirectory(src)

if(DTK_BUILD_TOOLS)
  add_subdirectory(tools)
endif(DTK_BUILD_TOOLS)

if(DTK_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(DTK_BUILD_EXAMPLES)

if(DTK_BUILD_REPORTING)
  include(dtkReporting)
endif(DTK_BUILD_REPORTING)

if(DTK_BUILD_TESTING)
  add_subdirectory(tests)
endif(DTK_BUILD_TESTING)

if(DTK_BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif(DTK_BUILD_DOCUMENTATION)

if(DTK_BUILD_TUTORIALS)
  add_subdirectory(tutorials)
endif(DTK_BUILD_TUTORIALS)
