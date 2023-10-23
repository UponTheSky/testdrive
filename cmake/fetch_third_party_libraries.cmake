# add third-party libraries
## references:
## https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html
## https://cmake.org/cmake/help/latest/module/FetchContent.html
## https://jonathanhamberg.com/post/2019-01-27-cmake-dependencies-fetch-content/
## https://www.glfw.org/docs/3.3/build_guide.html

include(FetchContent)

# glfw
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

# glad
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

# glm
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

# assimp
FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git)
FetchContent_MakeAvailable(assimp)
