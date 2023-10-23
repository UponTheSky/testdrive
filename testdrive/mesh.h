#pragma once

// stdlibs
#include <string>
#include <stdexcept>
#include <vector>

// externals
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// customs
#include "shader.h"


namespace model {
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Texture {
    unsigned int id;
    std::string type;
  };

  class Mesh {
    public:
      Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<Texture>& textures
      );

      void Draw(const Shader& shader) const;

      // TODO: deal with these legacies
      void BindVAO() const { glBindVertexArray(mVAO); }
      void UnbindVAO() const { glBindVertexArray(0); }
      void BindTexture(size_t index) const;
      void UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); }
      glm::mat4 GetTrans() const { return mTransformation; }

    private:
      // mesh data
      std::vector<Vertex> mVertices;
      std::vector<unsigned int> mIndices;
      std::vector<Texture> mTextures;

      // render data
      unsigned int mVAO, mVBO, mEBO;

      // TODO: deal with these legacies
      unsigned int _textures[2];
      glm::mat4 mTransformation;

    private:
      void SetupMesh();

      // legacies
      void _SetupTexture(const std::string& texturePath, size_t index);
  };
};
