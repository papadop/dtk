### CMakeLists.txt ---
## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

## #################################################################
## Essential layer
## #################################################################

add_subdirectory(dtk)
add_subdirectory(dtkCore)
#add_subdirectory(dtkComposer)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkLog)
add_subdirectory(dtkMath)
add_subdirectory(dtkMeta)
add_subdirectory(dtkTest)

## #################################################################
## Essential target
## #################################################################

set(DTK_TARGETS)
set(DTK_TARGETS ${DTK_TARGETS} dtkCore)
#set(DTK_TARGETS ${DTK_TARGETS} dtkComposer)
set(DTK_TARGETS ${DTK_TARGETS} dtkDistributed)
set(DTK_TARGETS ${DTK_TARGETS} dtkLog)
set(DTK_TARGETS ${DTK_TARGETS} dtkMath)
set(DTK_TARGETS ${DTK_TARGETS} dtkMeta)

## #################################################################
## Support layer
## #################################################################

if(DTK_BUILD_SUPPORT_COMPOSER)
add_subdirectory(dtkComposerSupport)
endif(DTK_BUILD_SUPPORT_COMPOSER)

if(DTK_BUILD_SUPPORT_CORE)
add_subdirectory(dtkCoreSupport)
endif(DTK_BUILD_SUPPORT_CORE)

if(DTK_BUILD_SUPPORT_CONTAINER)
add_subdirectory(dtkContainerSupport)
endif(DTK_BUILD_SUPPORT_CONTAINER)

if(DTK_BUILD_SUPPORT_DISTRIBUTED)
add_subdirectory(dtkDistributedSupport)
endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

if(DTK_BUILD_SUPPORT_GUI)
add_subdirectory(dtkGuiSupport)
endif(DTK_BUILD_SUPPORT_GUI)

if(DTK_BUILD_SUPPORT_MATH)
add_subdirectory(dtkMathSupport)
endif(DTK_BUILD_SUPPORT_MATH)

if(DTK_BUILD_SUPPORT_PLOT)
add_subdirectory(dtkPlotSupport)
endif(DTK_BUILD_SUPPORT_PLOT)

## #################################################################
## Support targets
## #################################################################

if(DTK_BUILD_SUPPORT_CORE)
set(DTK_TARGETS ${DTK_TARGETS} dtkCoreSupport)
endif(DTK_BUILD_SUPPORT_CORE)

if(DTK_BUILD_SUPPORT_CONTAINER)
set(DTK_TARGETS ${DTK_TARGETS} dtkContainerSupport)
endif(DTK_BUILD_SUPPORT_CONTAINER)

if(DTK_BUILD_SUPPORT_COMPOSER)
set(DTK_TARGETS ${DTK_TARGETS} dtkComposerSupport)
endif(DTK_BUILD_SUPPORT_COMPOSER)

if(DTK_BUILD_SUPPORT_DISTRIBUTED)
set(DTK_TARGETS ${DTK_TARGETS} dtkDistributedSupport)
endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

if(DTK_BUILD_SUPPORT_GUI)
set(DTK_TARGETS ${DTK_TARGETS} dtkGuiSupport)
endif(DTK_BUILD_SUPPORT_GUI)

if(DTK_BUILD_SUPPORT_MATH)
set(DTK_TARGETS ${DTK_TARGETS} dtkMathSupport)
endif(DTK_BUILD_SUPPORT_MATH)

if(DTK_BUILD_SUPPORT_PLOT)
set(DTK_TARGETS ${DTK_TARGETS} dtkPlotSupport)
endif(DTK_BUILD_SUPPORT_PLOT)

## #################################################################
## Target export
## #################################################################

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")

######################################################################
### CMakeLists.txt ends here
