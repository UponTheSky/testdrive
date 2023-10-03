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
      void Setup(
        float* vertices,
        unsigned int verticesSize,
        unsigned int* indices,
        unsigned int indicesSize
      );
      void BindVAO() const { glBindVertexArray(_VAO); }
      void UnbindVAO() const { glBindVertexArray(0); }

    private:
      unsigned int _VAO, _VBO, _EBO;
  };
};
