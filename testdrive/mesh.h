#pragma once

#include <string>
#include <stdexcept>
#include <vector>

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
      : _trans(trans), _VAO(0), _VBO(0), _EBO(0) {
        _textures[0] = 0;
        _textures[1] = 0;
      }

      virtual ~Mesh() = default;

      void Setup(
        float* vertices,
        unsigned int verticesSize,
        unsigned int* indices,
        unsigned int indicesSize,
        const std::vector<const char*>& texturePaths
      );

      void BindVAO() const { glBindVertexArray(_VAO); }
      void UnbindVAO() const { glBindVertexArray(0); }
      void BindTexture(size_t index) const;
      void UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); }
      glm::mat4 GetTrans() const { return _trans; }

    private:
      unsigned int _VAO, _VBO, _EBO;
      unsigned int _textures[2];
      glm::mat4 _trans;

      void _SetupTexture(const std::string& texturePath, size_t index);
  };
};
