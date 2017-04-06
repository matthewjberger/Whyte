cmake_minimum_required(VERSION 3.0)
project(Whyte)

# Project options
option(WHYTE_BUILD_UNIT_TESTS "Build the unit tests project for the Whyte engine." OFF)

# Unit Tests
if(WHYTE_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif(WHYTE_BUILD_UNIT_TESTS)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure C++14
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 14)

# Set the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Disable all warnings 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# GLAD requires libdl on Unix
if(NOT WIN32)
	set(GLAD_LIBRARIES dl) 
endif()

# Find Libraries
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_INCLUDE_DIR}
                    src/Renderer/OpenGL/glad/include/)

# Create file globs
file(GLOB HEADER_FILES src/*.h)
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB CONFIG_FILES CMakeLists.txt
                       Readme.md
                       .gitignore)

# Define source file groupings
source_group("Headers" FILES ${HEADER_FILES})
source_group("Source" FILES ${SOURCE_FILES})
source_group("Configs" FILES ${CONFIG_FILES})

# Define renderer-specific file globs and groupings
file(GLOB GLAD_SOURCE  src/Renderer/OpenGL/glad/src/glad.c)
source_group("Source\\Renderer\\OpenGL\\glad" FILES ${GLAD_SOURCE})

# Define the executable
add_executable(${PROJECT_NAME}  ${HEADER_FILES}
                                ${SOURCE_FILES}
                                ${CONFIG_FILES}
                                ${GLAD_SOURCE})

# Define the libraries to link against
target_link_libraries(${PROJECT_NAME}   ${SDL2_LIBRARY}
                                        ${GLAD_LIBRARIES})

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Visual Studio specific settings
# Requires CMake 3.8+
if(MSVC)
    # Set the startup project
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Set the working directory
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/debug)

    # Hide the console in visual studio projects in debug and release
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    # Copy dependencies to output folder
    add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
                                COMMAND ${CMAKE_COMMAND} -E copy
                                $ENV{SDL2DIR}/lib/win32/SDL2.dll
                                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(MSVC)
