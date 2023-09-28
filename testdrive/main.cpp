#include "window.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();

  while (!window->ShouldClose()) {


    window->SwapBuffers();
    window->PollEvents();
  }


  return 0;
}
