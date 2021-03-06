### FindQwt.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun  6 16:20:06 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Dec  9 13:29:20 2013 (+0100)
##           By: Selim Kraria
##     Update #: 46
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

# QWT_FOUND - system has Qwt
# QWT_INCLUDE_DIR - where to find qwt.h
# QWT_LIBRARIES - the libraries to link against to use Qwt
# QWT_LIBRARY - where to find the Qwt library (not for general use)

set(QWT_FOUND "NO")

if(QT4_FOUND)

  find_path(QWT_INCLUDE_DIR 
    NAMES qwt.h
    PATHS $ENV{QWT_DIR}/src
    $ENV{QWT_DIR}/include
    /user/skraria/home/tools/qwttmp/src
    /usr/local/qwt/include
    /usr/local/include
    /opt/qwt/include
    /usr/include/qwt
    /usr/include/qwt-qt4
    /usr/include)

  set(QWT_NAMES ${QWT_NAMES} qwt qwt-qt4 libqwt libqwt-qt4)

  find_library(QWT_LIBRARY
    NAMES ${QWT_NAMES}
    PATHS $ENV{QWT_DIR}/lib NO_DEFAULT_PATH)

  find_library(QWT_LIBRARY
    NAMES ${QWT_NAMES}
    PATHS /opt/qwt/lib /usr/local/qwt/lib /usr/local/lib /usr/lib)

  if(QWT_INCLUDE_DIR AND QWT_LIBRARY)
    set(QWT_LIBRARIES ${QWT_LIBRARY})
    set(QWT_FOUND "YES")

    if (CYGWIN)
      if(NOT BUILD_SHARED_LIBS)
        set(QWT_DEFINITIONS -DQWT_STATIC)
      endif(NOT BUILD_SHARED_LIBS)
    endif(CYGWIN)

  endif(QWT_INCLUDE_DIR AND QWT_LIBRARY)

endif(QT4_FOUND)

mark_as_advanced(QWT_INCLUDE_DIR QWT_LIBRARY QWT_DIR)
