cmake_minimum_required(VERSION 3.10)

project(interpreter)

add_executable(interpreter main.c)

target_include_directories(interpreter PUBLIC "${PROJECT_BINARY_DIR}/include")

add_subdirectory(include)
include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(interpreter PUBLIC parser)
target_link_libraries(interpreter PUBLIC variable)


