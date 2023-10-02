#include "window.h"
#include "renderer.h"
#include "mesh.h"
#include "shader.h"

int main() {

  window::GLFWwindowWrapper* window = window::GLFWwindowWrapper::GetInstance();
  render::Renderer renderer;
  render::RenderState* renderState = render::RenderState::GetInstance();

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

  model::Mesh mesh;
  Shader shader;

  mesh.Setup(vertices, sizeof(vertices));
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
