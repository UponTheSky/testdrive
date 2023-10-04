#include "window.h"
#include "renderer.h"
#include "mesh.h"
#include "shader.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();
  render::Renderer renderer;
  render::RenderState* renderState = render::RenderState::GetInstance();

  float vertices[] = {
    // positions // colors // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
  };
  unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
  };

  model::Mesh mesh;
  Shader shader;

  mesh.Setup(vertices, sizeof(vertices), indices, sizeof(indices), "resources/container.jpeg");
  shader.Build("shader/vertex.glsl", "shader/fragment.glsl");

  while (!window->ShouldClose()) {
    window->ProcessInput();

    renderer.RenderBackground(*renderState);
    renderer.RenderMesh(mesh, shader);

    window->PollEvents();
    window->SwapBuffers();
  }

  return 0;
}
