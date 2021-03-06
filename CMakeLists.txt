##---------------------------------------------------------------------------
## Author:      Dave Register
##***************************************************************************
## *   Copyright (C) 2010 by David S. Register                               *
## *   This program is free software; you can redistribute it and/or modify  *
## *   it under the terms of the GNU General Public License as published by  *
## *   the Free Software Foundation; either version 2 of the License, or     *
## *   (at your option) any later version.                                   *
## *                                                                         *
## *   This program is distributed in the hope that it will be useful,       *
## *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
## *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
## *   GNU General Public License for more details.                          *
## *                                                                         *
## *   You should have received a copy of the GNU General Public License     *
## *   along with this program; if not, write to the                         *
## *   Free Software Foundation, Inc.,                                       *
## *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
## ***************************************************************************

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
LIST(APPEND CMAKE_CXX_FLAGS " -std=c++14")
SET(CMAKE_BUILD_TYPE Debug)
# This should be 2.8.0 to have FindGTK2 module
IF (COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 OLD)
  CMAKE_POLICY(SET CMP0005 OLD)
  CMAKE_POLICY(SET CMP0011 OLD)
  CMAKE_POLICY(SET CMP0043 OLD)
  CMAKE_POLICY(SET CMP0046 OLD)
ENDIF (COMMAND cmake_policy)

PROJECT(marinetraffic_pi)

SET(PACKAGE_NAME marinetraffic_pi)
SET(PLUGIN_SOURCE_DIR ..)
MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

IF (PREFIX)
	SET(CMAKE_INSTALL_PREFIX ${PREFIX})
ENDIF (PREFIX)

SET(PARENT opencpn)
SET(PREFIX_BIN bin)
SET(PREFIX_INCLUDE include)
SET(PREFIX_DATA share)
SET(PREFIX_PARENTDATA ${PREFIX_DATA}/${PARENT})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# require proper c++
#ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-variadic-macros" )
#TODO: Should we use  -fno-stack-protector
#  IF NOT DEBUGGING CFLAGS="-O2 -march=native"
IF(NOT WIN32)
 ADD_DEFINITIONS( "-Wall -g -fexceptions -fvisibility=hidden" )

 IF(NOT APPLE)
  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
 ELSE(NOT APPLE)
  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
 ENDIF(NOT APPLE)

ENDIF(NOT WIN32)

# Add some definitions to satisfy MS
IF(WIN32)
    ADD_DEFINITIONS(-D__MSVC__)
    ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
ENDIF(WIN32)


SET(wxWidgets_USE_LIBS base core net xml html adv aui)
SET(BUILD_SHARED_LIBS TRUE)
FIND_PACKAGE(wxWidgets REQUIRED)

INCLUDE(${wxWidgets_USE_FILE})

FIND_PACKAGE(Gettext REQUIRED)

# Boost
SET(BOOST_ROOT C:/boost_1_60_0)
if(NOT EXISTS ${BOOST_ROOT} OR NOT IS_DIRECTORY ${BOOST_ROOT})
    SET(BOOST_ROOT C:/Develop/Libs/boost_1_61_0)
endif()
find_package(Boost COMPONENTS REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
# End Boost

# For convenience we define the sources as a variable. You can add 
# header files and cpp/c files and CMake will sort them out
SET(SRC_MARINETRAFFIC
		marinetraffic_pi.h
 		marinetraffic_pi.cpp
                DataReader.h
                DataReader.cpp
                CURLMarineExtractor.h
                CURLMarineExtractor.cpp
                FullShipInfo.h
                FullShipInfo.cpp
                InterfaceMTDialog.h
                InterfaceMTDialog.cpp
                MarineTrafficDialog.h
                MarineTrafficDialog.cpp
 	)

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_MARINETRAFFIC})

# Ace
#SET(ACE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ace)
#LIST(APPEND CMAKE_MODULE_PATH ${ACE_ROOT_DIR})
#find_package(ace REQUIRED)
#INCLUDE_DIRECTORIES(${ACE_INCLUDE_DIR})
#${CMAKE_CURRENT_BINARY_DIR}
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ace/lib/libACE.dll ${CMAKE_BINARY_DIR}/libACE.dll COPYONLY)
# End Ace
IF(WIN32)
  #SET(OPENCPN_IMPORT_LIB "../../../${CMAKE_CFG_INTDIR}/${PARENT}")
  #TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${OPENCPN_IMPORT_LIB} )
  #ADD_DEPENDENCIES(${PACKAGE_NAME} ${PARENT})
  INCLUDE("cmake/PluginInstall.cmake")
  INCLUDE("cmake/PluginLocalization.cmake")
  INCLUDE("cmake/PluginPackage.cmake")
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(${PACKAGE_NAME} ${wxWidgets_LIBRARIES})
#TARGET_LINK_LIBRARIES(${PACKAGE_NAME} ${ACE_LIBRARY})

file(COPY "data" DESTINATION "/")

IF(UNIX)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME LIBRARY DESTINATION ${PREFIX_PARENTDATA}/plugins)
ENDIF(UNIX)

IF(WIN32)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION "plugins")
message("prefix ${CMAKE_INSTALL_PREFIX}")
ENDIF(WIN32)
 	  	 
