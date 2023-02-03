# Equinox-Logger 2.0
# Author: Janusz Wolak
# Copylefts (C) 2022

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8.9)
project(EquinoxLogger)

set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(EQUINOX_LOGGER_TESTS			"Build tests"			ON)
option(EQUINOX_LOGGER_EXAMPLES		"Build examples"		ON)
option(EQUINOX_LOGGER_BUILD_SHARED	"Build shared lib"		ON)
option(EQUINOX_LOGGER_BUILD_STATIC	"Build static lib"		OFF)


set(EQUINOX_LOGGER_PUBLIC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/api
)

set(EQUINOX_LOGGER_INCLUDE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(EQUINOX_LOGGER_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger-LoggerEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger-ConsoleLogsProducer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger-FileLogsProducer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger-TimestampProducer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger-LogsProducer.cpp
)

if (EQUINOX_LOGGER_BUILD_SHARED)
	include_directories(EquinoxLogger PRIVATE  ${EQUINOX_LOGGER_INCLUDE} ${EQUINOX_LOGGER_PUBLIC_HEADERS})
	add_library(EquinoxLogger SHARED ${EQUINOX_LOGGER_SRC})
	target_compile_definitions(EquinoxLogger PUBLIC EQUINOX_SHARED_SHARED_LIB)
endif()

if (EQUINOX_LOGGER_BUILD_STATIC)
	include_directories(EquinoxLogger PRIVATE  ${EQUINOX_LOGGER_INCLUDE} ${EQUINOX_LOGGER_PUBLIC_HEADERS})
	add_library(EquinoxLogger STATIC ${EQUINOX_LOGGER_SRC})
endif()

if(EQUINOX_LOGGER_TESTS)
	add_subdirectory(tests)
endif(EQUINOX_LOGGER_TESTS)

if(EQUINOX_LOGGER_EXAMPLES)
	add_subdirectory(examples)
endif(EQUINOX_LOGGER_EXAMPLES)


