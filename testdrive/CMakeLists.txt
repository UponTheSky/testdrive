# Include the compiler config
include(compiler_config)

# set shared libs option
option(BUILD_SHARED_LIBS "build GLFW is built as a dynamic library" ON)

# include 3rd party libraries
include(fetch_third_party_libraries)

# add the main executable
add_executable(testdrive main.cpp window.cpp renderer.cpp)

# add libraries to the main executable
## macos frameworks: https://stackoverflow.com/questions/27585896/how-to-use-framework-using-cmake
set(macos_frameworks "-framework OpenGL;-framework Cocoa;-framework IOKit")
target_link_libraries(testdrive
  PRIVATE
  compiler_flags
  glfw glad
  glm
  ${macos_frameworks}
)

target_include_directories(testdrive
  PRIVATE
  ${glfw_SOURCE_DIR}/include/GLFW
  ${glad_BINARY_DIR}/include/glad
  ${glad_BINARY_DIR}/include/KHR
  ${glm_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)
