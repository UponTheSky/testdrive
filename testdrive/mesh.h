#pragma once

#include <string>
#include <stdexcept>

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
      Mesh(const glm::mat4& trans)
      : _trans(trans), _VAO(0), _VBO(0), _EBO(0), _texture(0) {}

      void Setup(
        float* vertices,
        unsigned int verticesSize,
        unsigned int* indices,
        unsigned int indicesSize,
        const std::string& texturePath
      );

      void BindVAO() const { glBindVertexArray(_VAO); }
      void UnbindVAO() const { glBindVertexArray(0); }
      void BindTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture);
      }
      void UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); }
      glm::mat4 GetTrans() const { return _trans; }

    private:
      unsigned int _VAO, _VBO, _EBO, _texture;
      glm::mat4 _trans;

      void _SetupTexture(const std::string& texturePath);
  };
};
