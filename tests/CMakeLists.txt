# Equinox-Logger 2.1.1
# Author: Janusz Wolak
# Copyright (C) 2026

cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_NAME EquinoxLoggerTests.x86)
project(${PROJECT_NAME})

set(EQUINOX_LOGGER_LIB_DIR ${PROJECT_SOURCE_DIR}/../libEquinoxLogger.so)

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(EQUINOX_LOGGER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)
set(EQUINOX_LOGGER_API_HEADER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../api)
set(EQUINOX_LOGGER_SRC_DIR ${PROJECT_SOURCE_DIR}/../src)

set(EQUINOX_LOGGER_SRC
	${EQUINOX_LOGGER_SRC_DIR}/EquinoxLoggerEngine.cpp
)

set(EQUINOX_LOGGER_TESTS_DIR
	${PROJECT_SOURCE_DIR}/src/
)

set(EQUINOX_LOGGER_TESTS_SRC
	${EQUINOX_LOGGER_TESTS_DIR}/TimestampProducerTests.cpp
	${EQUINOX_LOGGER_TESTS_DIR}/MultipleThreadsTest.cpp
	
)

set(EQUINOX_LOGGER_MOCKS_INCLUDE_DIR
	${PROJECT_SOURCE_DIR}/Mocks
)

include_directories(${EQUINOX_LOGGER_INCLUDE_DIR} ${EQUINOX_LOGGER_MOCKS_INCLUDE_DIR} ${EQUINOX_LOGGER_MOCKS_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${EQUINOX_LOGGER_SRC} ${EQUINOX_LOGGER_TESTS_SRC})

add_dependencies (${PROJECT_NAME} EquinoxLogger)                      #to build libEquinoxLogger before try to link it
target_link_libraries(${PROJECT_NAME} gmock gtest gtest_main pthread)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} gtest_main)
target_link_libraries(${PROJECT_NAME} ${EQUINOX_LOGGER_LIB_DIR})