#pragma once

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// custom libraries
#include "vector.h"

namespace render {
  class RenderState {
    public:
      static RenderState* GetInstance();
      Vec4 GetBackgroundColor() const;

    private:
      RenderState(const Vec4& backgroundColor);
      static RenderState* _instance;
      Vec4 _backgroundColor;
  };

  class Renderer {
    public:
      Renderer() = default;

      void Render(RenderState& state);
  };
};
