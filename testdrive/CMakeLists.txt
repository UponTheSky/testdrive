# Include the compiler config
include(CompilerConfig)

# set shared libs option
option(BUILD_SHARED_LIBS "build GLFW is built as a dynamic library" ON)

# include 3rd party libraries
include(FetchThirdParties)

# add the main executable
add_executable(TestDrive main.cpp)

# add libraries to the main executable
## macos frameworks: https://stackoverflow.com/questions/27585896/how-to-use-framework-using-cmake
set(macos_frameworks "-framework OpenGL;-framework Cocoa;-framework IOKit")
target_link_libraries(TestDrive PRIVATE compiler_flags glfw glad ${macos_frameworks})

target_include_directories(TestDrive
  PRIVATE
  ${glfw_SOURCE_DIR}/include/GLFW
  ${glad_BINARY_DIR}/include/glad
  ${glad_BINARY_DIR}/include/KHR
)