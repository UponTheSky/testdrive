#pragma once

// STL
#include <string>
#include <stdexcept>
#include <cassert>

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// custom headers
#include "consts.h"
#include "renderer.h"
#include "camera.h"

/**
 * The namespace related to the window object.
 * The window object should be maintained as a singleton object.
*/
namespace window {

  // Window object created by the GLFW library
  class GLFWwindowWrapper {
    public:
      static GLFWwindowWrapper* GetInstance();
      ~GLFWwindowWrapper();

      void Terminate() const;
      bool ShouldClose() const;
      void SwapBuffers() const;
      void PollEvents() const;

      void ProcessInput(Camera& camera) const;
      void SetWindowOptions() const;

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
  void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}
