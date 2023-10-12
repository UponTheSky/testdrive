#include "camera.h"
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

    // set callbacks
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(glfw_window, mouse_callback);
    glfwSetScrollCallback(glfw_window, scroll_callback);

    // load OpenGL functions(GLAD)
    LoadOpenGLFunctions();

    _instance = new GLFWwindowWrapper(glfw_window);
  }

  return _instance;
}

window::GLFWwindowWrapper::GLFWwindowWrapper(GLFWwindow* glfw_window)
: _glfw_window(glfw_window) {}

void window::GLFWwindowWrapper::ProcessInput(Camera& camera) const {
  render::RenderState* renderState = render::RenderState::GetInstance();

  float currentFrame = static_cast<float>(glfwGetTime());
  float cameraSpeed = 2.5f * (currentFrame - renderState->GetLastFrame());
  renderState->SetLastFrame(currentFrame);

  if (glfwGetKey(_glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_glfw_window, true);
  }

  if (glfwGetKey(_glfw_window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.SetPosition(camera.GetPosition() + cameraSpeed * camera.GetDirection());
  }

  if (glfwGetKey(_glfw_window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.SetPosition(camera.GetPosition() - cameraSpeed * camera.GetDirection());
  }

  if (glfwGetKey(_glfw_window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.SetPosition(camera.GetPosition() - camera.GetRight() * cameraSpeed);
  }

  if (glfwGetKey(_glfw_window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.SetPosition(camera.GetPosition() + camera.GetRight() * cameraSpeed);
  }
}

void window::GLFWwindowWrapper::SetWindowOptions() const {
  glfwSetInputMode(_glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

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

void window::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  const float sensitivity = 0.1f;
  Camera* camera = Camera::GetCamera(std::string("testCamera"));

  float xoffset = (xpos - camera->GetLastX()) * sensitivity;
  float yoffset = (camera->GetLastY() - ypos) * sensitivity;

  camera->SetLastX(xpos);
  camera->SetLastY(ypos);

  camera->SetXaxisRotation(glm::radians(xoffset));
  camera->SetYaxisRotation(glm::radians(yoffset));
}

void window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  Camera* camera = Camera::GetCamera(std::string("testCamera"));
  camera->SetFov(camera->GetFov() - static_cast<float>(yoffset));

  if (camera->GetFov() < 1.0f) {
    camera->SetFov(1.0f);
  } else if (camera->GetFov() > 45.0f) {
    camera->SetFov(45.0f);
  }
}
