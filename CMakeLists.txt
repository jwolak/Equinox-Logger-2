# Equinox-Logger 2.0
# Author: Janusz Wolak
# Copyright (C) 2023

#------------------------------------------------------------------------------------------
#                                cmake settings
#------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22.1)

#------------------------------------------------------------------------------------------
#                                Project settings
#------------------------------------------------------------------------------------------
project(EquinoxLogger)

set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------------------------------------------------------------------------------
#                                Project options
#------------------------------------------------------------------------------------------

option(EQUINOX_LOGGER_TESTS         "Build tests"           ON)
option(EQUINOX_LOGGER_EXAMPLES      "Build examples"        ON)
option(EQUINOX_LOGGER_BUILD_SHARED  "Build shared lib"      ON)
option(EQUINOX_LOGGER_BUILD_STATIC  "Build static lib"      OFF)

#------------------------------------------------------------------------------------------
#                                Project api
#------------------------------------------------------------------------------------------
set(EQUINOX_LOGGER_API
	${CMAKE_CURRENT_SOURCE_DIR}/api
)

#------------------------------------------------------------------------------------------
#                                Project include
#------------------------------------------------------------------------------------------
set(EQUINOX_LOGGER_INCLUDE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

#------------------------------------------------------------------------------------------
#                                Project source
#------------------------------------------------------------------------------------------
set(EQUINOX_LOGGER_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLoggerEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLoggerEngineImpl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/EquinoxLogger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/AsyncLogQueue.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TimestampProducer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ConsoleLogsProducer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/FileLogsProducer.cpp
)

#------------------------------------------------------------------------------------------
#                                Project target
#------------------------------------------------------------------------------------------
if (EQUINOX_LOGGER_BUILD_SHARED)
	include_directories(EquinoxLogger PRIVATE  ${EQUINOX_LOGGER_INCLUDE} ${EQUINOX_LOGGER_API})
	add_library(EquinoxLogger SHARED ${EQUINOX_LOGGER_SRC})
	target_compile_definitions(EquinoxLogger PUBLIC EQUINOX_SHARED_SHARED_LIB)
endif()

if (EQUINOX_LOGGER_BUILD_STATIC)
	include_directories(EquinoxLogger PRIVATE  ${EQUINOX_LOGGER_INCLUDE} ${EQUINOX_LOGGER_API})
	add_library(EquinoxLogger STATIC ${EQUINOX_LOGGER_SRC})
endif()

#------------------------------------------------------------------------------------------
#                                Project tests
#------------------------------------------------------------------------------------------
if(EQUINOX_LOGGER_TESTS)
	add_subdirectory(tests)
endif(EQUINOX_LOGGER_TESTS)

#------------------------------------------------------------------------------------------
#                                Project examples
#------------------------------------------------------------------------------------------
if(EQUINOX_LOGGER_EXAMPLES)
	add_subdirectory(examples)
endif(EQUINOX_LOGGER_EXAMPLES)

#------------------------------------------------------------------------------------------
#                                Project install
#------------------------------------------------------------------------------------------
install(FILES ${EQUINOX_LOGGER_API}/EquinoxLogger.h
              ${EQUINOX_LOGGER_API}/EquinoxLoggerCommon.h
              ${EQUINOX_LOGGER_API}/EquinoxLoggerEngine.h
        DESTINATION include)

install(TARGETS EquinoxLogger DESTINATION lib)
install(FILES EquinoxLoggerConfig.cmake DESTINATION lib/cmake/EquinoxLogger)


