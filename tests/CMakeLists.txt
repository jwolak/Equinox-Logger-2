# Equinox-Logger 2.0 unit tests
# Author: Janusz Wolak
# Copylefts (C) 2022

cmake_minimum_required(VERSION 2.8.9)

set(PROJECT_NAME EquinoxLoggerTests.x86)
project(${PROJECT_NAME})

set(EQUINOX_LOGGER_LIB_DIR ${PROJECT_SOURCE_DIR}/../libEquinoxLogger.so)

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(EQUINOX_LOGGER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)
set(EQUINOX_LOGGER_API_HEADER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../)
set(EQUINOX_LOGGER_SRC_DIR ${PROJECT_SOURCE_DIR}/../src)

set(EQUINOX_LOGGER_SRC
	${EQUINOX_LOGGER_SRC_DIR}/EquinoxLogger-LoggerEngine.cpp
	${EQUINOX_LOGGER_SRC_DIR}/EquinoxLogger-LoggerEngineLogic.cpp
	${EQUINOX_LOGGER_SRC_DIR}/EquinoxLogger-LoggerManager.cpp
)

set(EQUINOX_LOGGER_TESTS_DIR
	${PROJECT_SOURCE_DIR}/src/
)

set(EQUINOX_LOGGER_TESTS_SRC
	${EQUINOX_LOGGER_TESTS_DIR}/TimestampProducerTests.cpp
	${EQUINOX_LOGGER_TESTS_DIR}/LogsProducerTests.cpp
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