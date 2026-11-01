cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
	message(FATAL_ERROR "GEODE_SDK environment variable is not set. Point it at your Geode SDK folder.")
endif()

set(GEODE_SDK "$ENV{GEODE_SDK}")
set(CMAKE_MODULE_PATH "${GEODE_SDK}/cmake")
set(CPM_SOURCE_CACHE "$ENV{CPM_SOURCE_CACHE}")

project(perfmode VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory("${GEODE_SDK}" geode-sdk)

add_library(${PROJECT_NAME} SHARED
	src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

setup_geode_mod(${PROJECT_NAME})
