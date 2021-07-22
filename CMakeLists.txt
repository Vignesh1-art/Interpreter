cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE "Debug")

project(vinterpreter)

add_executable(vinterpreter main.c)


add_subdirectory(src)

target_include_directories(vinterpreter PUBLIC "${PROJECT_BINARY_DIR}/src")

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(vinterpreter PUBLIC parser)
target_link_libraries(vinterpreter PUBLIC interpreter)


