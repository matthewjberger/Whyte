cmake_minimum_required(VERSION 3.1)
project(Whyte VERSION 0.1.0 LANGUAGES CXX)

# Set the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Find Libraries
find_package(SDL2 REQUIRED)

# Create file globs
file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB CONFIG_FILES CMakeLists.txt
                       Readme.md)

# Define source file groupings
source_group("Headers" FILES ${HEADER_FILES})
source_group("Source" FILES ${SOURCE_FILES})
source_group("Configs" FILES ${CONFIG_FILES})

# Define the executable
add_library(${PROJECT_NAME}	${HEADER_FILES}
							${SOURCE_FILES}
							${CONFIG_FILES})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR} 
	include 
	${CMAKE_SOURCE_DIR}/src/renderer/include
	${CMAKE_SOURCE_DIR}/src/renderer/include/internal
	${CMAKE_SOURCE_DIR}/src/renderer/include/internal/backends/OpenGL)

# List necessary compiler features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_strong_enums cxx_nullptr)

# Define the libraries to link against
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY} Whyre)

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