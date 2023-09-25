#include "window.h"

window::GLFWwindowWrapper* window::GLFWwindowWrapper::_instance = nullptr;

window::GLFWwindowWrapper* window::GLFWwindowWrapper::GetInstance() {
  if (_instance == 0) {
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
    _instance = new GLFWwindowWrapper(glfw_window);
  }

  return _instance;
}

window::GLFWwindowWrapper::GLFWwindowWrapper(GLFWwindow* glfw_window)
: _glfw_window(glfw_window) {}

window::GLFWwindowWrapper::~GLFWwindowWrapper() {
  Terminate();
}

void window::GLFWwindowWrapper::Terminate() {
  glfwTerminate();
}

void window::LoadOpenGLFunctions() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
}
