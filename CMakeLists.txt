cmake_minimum_required(VERSION 3.1)
project(MasterSolution VERSION 0.1.0 LANGUAGES CXX)

# Project Options
option(WHYTE_BUILD_UNIT_TESTS "Build the unit tests for the Whyte engine." OFF)
option(WHYTE_BUILD_DEMOS "Build the demo projects for the Whyte engine." OFF)
option(WHYTE_BUILD_SANDBOX "Build an isolated, empty project that links against the Whyte engine." OFF)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure C++14
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 14)

# Set the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Find Libraries
find_package(SDL2 REQUIRED)

# Build the window library
#add_subdirectory(src/window)

# Build the renderer
add_subdirectory(src/renderer)

# Build the core
add_subdirectory(src/core)

# Unit Tests
if(WHYTE_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif(WHYTE_BUILD_UNIT_TESTS)

# Demos
if(WHYTE_BUILD_DEMOS)
    add_subdirectory(demos/window)
endif(WHYTE_BUILD_DEMOS)

# Sandbox
if(WHYTE_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif(WHYTE_BUILD_SANDBOX)
