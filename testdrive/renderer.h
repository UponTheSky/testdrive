#pragma once

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace render {
  class RenderState {
    public:
      static RenderState* GetInstance();
      glm::vec4 GetBackgroundColor() const;

    private:
      RenderState(const glm::vec4& backgroundColor);
      static RenderState* _instance;
      glm::vec4 _backgroundColor;
  };

  class Renderer {
    public:
      Renderer() = default;

      void Render(RenderState& state);
  };
};
