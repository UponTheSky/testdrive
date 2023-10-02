#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace model {
  struct Vertex {
    glm::vec3 Position;
  };

  class Mesh {
    public:
      Mesh() = default;
      void Setup(float* vertices, unsigned int verticesSize);
      void BindVAO() const { glBindVertexArray(_VAO); };

    private:
      unsigned int _VAO, _VBO;
  };
};
