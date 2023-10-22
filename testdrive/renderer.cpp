#include "renderer.h"

render::RenderState* render::RenderState::_instance = nullptr;

render::RenderState* render::RenderState::GetInstance() {
  if (_instance == nullptr) {
    _instance = new RenderState({ 0.1f, 0.1f, 0.1f, 1.0f });
  }
  return _instance;
}

render::RenderState::RenderState(
  const glm::vec4& backgroundColor) :
_backgroundColor(backgroundColor),
_lastFrame(0) {}

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
}

void render::Renderer::RenderMesh(
  const model::Mesh& mesh,
  const Shader& shader,
  Camera& camera,
  const Light& light
) {
  shader.Use();
  shader.SetUniformInt("material.diffuse", 0);
  shader.SetUniformInt("material.specular", 1);
  shader.SetUniformFloat("material.shininess", 32.0f);

  // glDrawArrays(GL_TRIANGLES, 0, 3);

  /** temporary part for learning purpose */
  shader.SetUniformMat4("model", mesh.GetTrans());

  camera.BuildView();
  camera.BuildProjection();

  shader.SetUniformMat4("view", camera.GetView());
  shader.SetUniformMat4("projection", camera.GetProjection());
  shader.SetUniformVec3("viewPos", camera.GetPosition());

  shader.SetUniformVec3("lightPos", light.GetPosition());
  shader.SetUniformVec3("light.ambient", glm::vec3(0.1f) * light.GetColor());
  shader.SetUniformVec3("light.diffuse", glm::vec3(0.5f) * light.GetColor());
  shader.SetUniformVec3("light.specular", glm::vec3(1.0f));


  /* ------------------------------------ */
  mesh.BindVAO();
  mesh.BindTexture(0);
  mesh.BindTexture(1);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  mesh.UnbindVAO();
  mesh.UnbindTexture();
}

void render::Renderer::RenderLight(const Light& light, const Shader& shader, Camera& camera) {
  shader.Use();

  // glDrawArrays(GL_TRIANGLES, 0, 3);

  /** temporary part for learning purpose */
  shader.SetUniformMat4("model", light.GetTrans());

  camera.BuildView();
  camera.BuildProjection();

  shader.SetUniformMat4("view", camera.GetView());
  shader.SetUniformMat4("projection", camera.GetProjection());

  shader.SetUniformVec3("lightColor", light.GetColor());

  /* ------------------------------------ */
  light.BindVAO();
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  light.UnbindVAO();
}

void render::Renderer::ClearBuffers() const {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void render::Renderer::SetRenderOptions() const {
  glEnable(GL_DEPTH_TEST);
}
