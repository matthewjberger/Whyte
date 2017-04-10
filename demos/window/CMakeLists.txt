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