#pragma once

// STL
#include <string>
#include <stdexcept>
#include <cassert>

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * The namespace related to the window object.
 * The window object should be maintained as a singleton object.
*/
namespace window {
  // initial window width, height, and title
  const unsigned int INIT_WINDOW_WIDTH = 800;
  const unsigned int INIT_WINDOW_HEIGHT = 600;
  const std::string INIT_WINDOW_TITLE = "Test Drive Renderer";

  // Window object created by the GLFW library
  class GLFWwindowWrapper {
    public:
      static GLFWwindowWrapper* GetInstance();
      ~GLFWwindowWrapper();

      void Terminate() const;
      bool ShouldClose() const;
      void SwapBuffers() const;
      void PollEvents() const;

    private:
      // singleton
      GLFWwindowWrapper(GLFWwindow* window);
      static GLFWwindowWrapper* _instance;

      // instance members
      GLFWwindow* _glfw_window;
  };

  // Load all OpenGL functions using the glfw loader function
  // see: https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library
  void LoadOpenGLFunctions();

  // callbacks
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
