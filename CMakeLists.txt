# CMake version
cmake_minimum_required(VERSION 3.27)

# Project name & version
project(TestDrive VERSION 1.0)

# Compiler flags as a library target
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# macos frameworks: https://stackoverflow.com/questions/27585896/how-to-use-framework-using-cmake
set(macos_frameworks "-framework OpenGL;-framework Cocoa;-framework IOKit")
## no -Wall; effective cmake(https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wno-deprecated;-fcolor-diagnostics;-fansi-escape-codes;-g>>"
)


# set shared libs option
option(BUILD_SHARED_LIBS "build GLFW is built as a dynamic library" ON)

# add third-party libraries
## references:
## https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html
## https://cmake.org/cmake/help/latest/module/FetchContent.html
## https://jonathanhamberg.com/post/2019-01-27-cmake-dependencies-fetch-content/
## https://www.glfw.org/docs/3.3/build_guide.html

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git)
FetchContent_GetProperties(glad)
if (NOT glad_POPULATED)
  set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
  set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
  set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
  set(GLAD_SPEC "gl" CACHE STRING "Name of the spec or list of multiple specs (separated by semicolons).")
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_populate(glad)
  add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

# add the main executable
add_executable(TestDrive main.cpp)

# add libraries to the main executable
target_link_libraries(TestDrive PRIVATE compiler_flags glfw glad ${macos_frameworks})

target_include_directories(TestDrive
  PRIVATE
  ${glfw_SOURCE_DIR}/include/GLFW
  ${glad_BINARY_DIR}/include/glad
  ${glad_BINARY_DIR}/include/KHR
)
