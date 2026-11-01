cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Accept the SDK path from the environment (CI sets GEODE_SDK) or from -DGEODE_SDK=...
if (NOT GEODE_SDK)
	if (DEFINED ENV{GEODE_SDK})
		set(GEODE_SDK "$ENV{GEODE_SDK}")
	else()
		message(FATAL_ERROR "GEODE_SDK is not set. Point it at your Geode SDK folder.")
	endif()
endif()

file(TO_CMAKE_PATH "${GEODE_SDK}" GEODE_SDK)

project(perfmode VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory("${GEODE_SDK}" geode-sdk)

add_library(${PROJECT_NAME} SHARED
	src/main.cpp
	src/Stats.cpp
	src/Cull.cpp
	src/CullLayer.cpp
	src/CullParticles.cpp
	src/CullLabels.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

setup_geode_mod(${PROJECT_NAME})
