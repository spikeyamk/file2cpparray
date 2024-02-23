cmake_minimum_required(VERSION 3.13)
project(file2cpparray C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
