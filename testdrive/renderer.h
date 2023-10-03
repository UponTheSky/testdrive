#pragma once

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.h"
#include "shader.h"

namespace render {
  class RenderState {
    public:
      static RenderState* GetInstance();
      glm::vec4 GetBackgroundColor() const;

    private:
      static RenderState* _instance;
      glm::vec4 _backgroundColor;

      RenderState(const glm::vec4& backgroundColor);
  };

  class Renderer {
    public:
      Renderer() = default;

      void RenderBackground(const RenderState& state);
      void RenderMesh(const model::Mesh& mesh, const Shader& shader);
  };
};
