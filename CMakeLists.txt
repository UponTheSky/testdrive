# CMake version
cmake_minimum_required(VERSION 3.27)

# Project name & version
project(TestDrive VERSION 1.0)

# CMake directory path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# include the source directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/testdrive)
