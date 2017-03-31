cmake_minimum_required(VERSION 3.0)
project(UnitTests)

# Group files
file(GLOB CATCH_HEADER Catch.hpp)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

# Specify Visual Studio solution filters
source_group("Catch" FILES ${CATCH_HEADER})
source_group("Tests" FILES ${PROJECT_SOURCES})
source_group("Configs" FILES ${PROJECT_CONFIGS})

# Specify the executable to create using the file globs
add_executable(${PROJECT_NAME}  ${CATCH_HEADER}
                                ${PROJECT_SOURCES}
                                ${PROJECT_CONFIGS})