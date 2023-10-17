#pragma once

// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "light.h"

namespace render {
  class RenderState {
    public:
      static RenderState* GetInstance();

      glm::vec4 GetBackgroundColor() const;
      float GetLastFrame() const { return _lastFrame; }
      void SetLastFrame(float lastFrame) { _lastFrame = lastFrame; }

    private:
      // singleton pattern
      static RenderState* _instance;
      RenderState(const glm::vec4& backgroundColor);

      // state variables
      glm::vec4 _backgroundColor;
      float _lastFrame;
  };

class Renderer {
    public:
      Renderer() = default;

      void ClearBuffers() const;
      void SetRenderOptions() const;
      void RenderBackground(const RenderState& state);
      void RenderMesh(const model::Mesh& mesh, const Shader& shader, Camera& camera, const Light& light);
      void RenderLight(const Light& light, const Shader& shader, Camera& camera);
  };
};
