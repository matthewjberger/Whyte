cmake_minimum_required(VERSION 3.1)
project(Whyte VERSION 0.1.0 LANGUAGES CXX)

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

# GLAD requires libdl on Unix
if(NOT WIN32)
	set(GLAD_LIBRARIES dl)
endif()

# Find Libraries
find_package(SDL2 REQUIRED)

# Create file globs
file(GLOB_RECURSE HEADER_FILES src/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB CONFIG_FILES CMakeLists.txt
                       Readme.md
                       .gitignore)

# Define source file groupings
source_group("Headers" FILES ${HEADER_FILES})
source_group("Source" FILES ${SOURCE_FILES})
source_group("Configs" FILES ${CONFIG_FILES})

# Define renderer-specific file globs and groupings
file(GLOB GLAD_SOURCE  third_party/glad/src/glad.c)
source_group("Source\\Third Party\\glad" FILES ${GLAD_SOURCE})

# Define the executable
add_library(${PROJECT_NAME}	${HEADER_FILES}
							${SOURCE_FILES}
							${CONFIG_FILES}
							${GLAD_SOURCE})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR}
												  third_party/glad/include/)

# List necessary compiler features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_strong_enums cxx_nullptr)

# Define the libraries to link against
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY}
											 ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES

	# Output to lib directory
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib

	# Output to bin directory
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin

	# Disable all warnings
	CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w"
)

# Build shared libraries
if(BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE "WHYTE_BUILD_DLL")
	target_compile_definitions(${PROJECT_NAME} INTERFACE "WHYTE_DLL")
endif(BUILD_SHARED_LIBS)

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
