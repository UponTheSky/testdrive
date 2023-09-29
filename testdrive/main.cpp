#include "window.h"
#include "renderer.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();
  render::Renderer renderer;
  render::RenderState* renderState = render::RenderState::GetInstance();

  while (!window->ShouldClose()) {
    window->ProcessInput();

    renderer.Render(*renderState);

    window->PollEvents();
    window->SwapBuffers();
  }


  return 0;
}
