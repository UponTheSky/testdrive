#include "window.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();

  while (!window->ShouldClose()) {
    window->ProcessInput();

    window->PollEvents();
    window->SwapBuffers();
  }


  return 0;
}
