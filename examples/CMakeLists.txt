# Equinox-Logger Examples 2.0
# Author: Janusz Wolak
# Copylefts (C) 2023

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
project(EquinoxLoggerExamples)

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EQUINOX_LOGGER_LIB_DIR ${PROJECT_SOURCE_DIR}/../libEquinoxLogger.so)

set(EQUINOX_LOGGER_API_HEADER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../)

set(EQUINOX_LOGGER_EXAMPLER_SRC_DIR
    ${PROJECT_SOURCE_DIR}/src
)

set(EQUINOX_LOGGER_EXAMPLES_SRC
    ${EQUINOX_LOGGER_EXAMPLER_SRC_DIR}/main.cpp
)

include_directories(${EQUINOX_LOGGER_API_HEADER_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${EQUINOX_LOGGER_EXAMPLES_SRC})
add_dependencies (${PROJECT_NAME} EquinoxLogger)                 #to build libEquinoxLogger before try to link it
target_link_libraries(${PROJECT_NAME} ${EQUINOX_LOGGER_LIB_DIR})