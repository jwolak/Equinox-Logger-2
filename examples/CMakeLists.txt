# Equinox-Logger 2.0
# Author: Janusz Wolak
# Copyright (C) 2023

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
    ${EQUINOX_LOGGER_EXAMPLER_SRC_DIR}/EquinoxLoggerExamples.cpp
)

include_directories(${EQUINOX_LOGGER_PUBLIC_HEADERS})
add_executable(${PROJECT_NAME} ${EQUINOX_LOGGER_EXAMPLES_SRC})
add_dependencies (${PROJECT_NAME} EquinoxLogger)                 #to build libEquinoxLogger before try to link it
target_link_libraries(${PROJECT_NAME} ${EQUINOX_LOGGER_LIB_DIR})