#include "window.h"
#include "renderer.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();
  render::Renderer renderer;
  render::RenderState* renderState = render::RenderState::GetInstance();

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };


  while (!window->ShouldClose()) {
    window->ProcessInput();

    renderer.Render(*renderState);

    window->PollEvents();
    window->SwapBuffers();
  }


  return 0;
}
