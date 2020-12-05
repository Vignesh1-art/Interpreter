cmake_minimum_required(VERSION 3.10)

project(vinterpreter)

add_executable(vinterpreter main.c)

target_include_directories(vinterpreter PUBLIC "${PROJECT_BINARY_DIR}/include")

add_subdirectory(include)
include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vinterpreter PUBLIC parser)
target_link_libraries(vinterpreter PUBLIC interpreter)


