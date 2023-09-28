#include "window.h"

#include <iostream>

// static variables should be defined(even if it is in-class defined) separately in the .cpp file
window::GLFWwindowWrapper* window::GLFWwindowWrapper::_instance = nullptr;

window::GLFWwindowWrapper* window::GLFWwindowWrapper::GetInstance() {
  if (_instance == nullptr) {
    // set up the window config
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // generate the window object
    GLFWwindow* glfw_window = glfwCreateWindow(
      INIT_WINDOW_WIDTH,
      INIT_WINDOW_HEIGHT,
      INIT_WINDOW_TITLE.c_str(),
      nullptr,
      nullptr
    );

    if (glfw_window == nullptr) {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfw_window); // don't forget it!

    // load OpenGL functions(GLAD)
    LoadOpenGLFunctions();

    // set up the viewport
    glViewport(0, 0, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

    _instance = new GLFWwindowWrapper(glfw_window);
  }

  return _instance;
}

window::GLFWwindowWrapper::GLFWwindowWrapper(GLFWwindow* glfw_window)
: _glfw_window(glfw_window) {}

/* glfw function wrapped */
window::GLFWwindowWrapper::~GLFWwindowWrapper() {
  Terminate();
}

void window::GLFWwindowWrapper::Terminate() const {
  glfwTerminate();
}

bool window::GLFWwindowWrapper::ShouldClose() const {
  assert(_glfw_window != nullptr);
  return glfwWindowShouldClose(_glfw_window);
}

void window::GLFWwindowWrapper::SwapBuffers() const {
  assert(_glfw_window != nullptr);
  glfwSwapBuffers(_glfw_window);
}

void window::GLFWwindowWrapper::PollEvents() const {
  glfwPollEvents();
}

void window::LoadOpenGLFunctions() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
}

/* window callbacks */
void window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
