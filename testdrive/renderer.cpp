#include "renderer.h"

render::RenderState* render::RenderState::_instance = nullptr;

render::RenderState* render::RenderState::GetInstance() {
  if (_instance == nullptr) {
    _instance = new RenderState({ 0.2f, 0.3f, 0.3f, 1.0f });
  }
  return _instance;
}

render::RenderState::RenderState(const glm::vec4& backgroundColor)
: _backgroundColor(backgroundColor) {}

glm::vec4 render::RenderState::GetBackgroundColor() const {
  return _backgroundColor;
}

void render::Renderer::RenderBackground(const RenderState& state) {
  glClearColor(
    state.GetBackgroundColor()[0],
    state.GetBackgroundColor()[1],
    state.GetBackgroundColor()[2],
    state.GetBackgroundColor()[3]
  );

  glClear(GL_COLOR_BUFFER_BIT);
}

void render::Renderer::RenderMesh(const model::Mesh& mesh, const Shader& shader) {
  shader.Use();
  mesh.BindVAO();
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  mesh.UnbindVAO();
}
