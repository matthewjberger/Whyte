cmake_minimum_required(VERSION 3.0)
project(Whyte_Example_Window)

# Group files
file(GLOB PROJECT_HEADERS *.h)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

# Specify Visual Studio solution filters
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Source" FILES ${PROJECT_SOURCES})
source_group("Configs" FILES ${PROJECT_CONFIGS})

# Specify the executable to create using the file globs
add_executable(${PROJECT_NAME}  ${PROJECT_HEADERS}
                                ${PROJECT_SOURCES}
                                ${PROJECT_CONFIGS})

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demos/${PROJECT_NAME})

# Set path to Whyte headers
target_include_directories(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:Whyte,INTERFACE_INCLUDE_DIRECTORIES>)

# Link against Whyte
target_link_libraries(${PROJECT_NAME} PRIVATE Whyte $<TARGET_PROPERTY:Whyte,INTERFACE_LINK_LIBRARIES>)

# Use any necessary compile features specified by Whyte
target_compile_features(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:Whyte,INTERFACE_COMPILE_FEATURES>)

# Use the interface compile definitions specified by Whyte
target_compile_definitions(${PROJECT_NAME} INTERFACE $<TARGET_PROPERTY:Whyte,INTERFACE_COMPILE_DEFINITIONS>)

# Visual Studio specific settings
# Requires CMake 3.8+
if(MSVC)
    # Hide the console in visual studio projects in debug and release
    set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS" 
		LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

	# Copy Whyte dependencies to output folder
	# SDL2
	add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
								COMMAND ${CMAKE_COMMAND} -E copy
								$ENV{SDL2DIR}/lib/win32/SDL2.dll
								$<TARGET_FILE_DIR:${PROJECT_NAME}>)

	# Dynamically linked
	if(BUILD_SHARED_LIBS) 
		# Copy Whyte library to output folder
		add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
									COMMAND ${CMAKE_COMMAND} -E copy
									$<TARGET_FILE:Whyte>
									$<TARGET_FILE_DIR:${PROJECT_NAME}>)

		# Copy Whyre library to output folder
		add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
									COMMAND ${CMAKE_COMMAND} -E copy
									$<TARGET_FILE:Whyre>
									$<TARGET_FILE_DIR:${PROJECT_NAME}>)
	endif(BUILD_SHARED_LIBS)
endif(MSVC)

