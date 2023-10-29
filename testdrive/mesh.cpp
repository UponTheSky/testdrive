#include <iostream>
#include "mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

model::Mesh::Mesh(
  const std::vector<Vertex>& vertices,
  const std::vector<unsigned int>& indices,
  const std::vector<Texture>& textures
) : mVertices(std::move(vertices)), mIndices(std::move(indices)), mTextures(textures)
{
  SetupMesh();
}

void model::Mesh::SetupMesh()
{
  // setup vao
  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

  // setup vbo
  glGenBuffers(1, &mVBO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

  // setup ebo
  glGenBuffers(1, &mEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

  // set vertex attrib pointers
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // position
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); // normal
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, TexCoords)); // texture

  glBindVertexArray(0);
}

void model::Mesh::Draw(const Shader& shader) const
{
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;

  // set textures
  for (unsigned int i = 0; i < mTextures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number = mTextures[i].type == "texture_diffuse"
    ? std::to_string(diffuseNr++)
    : std::to_string(specularNr++);

    // material.texture_diffuse1; material.texture_specular2; etc.
    shader.SetUniformFloat(("material." + mTextures[i].type + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
  }

  // draw
  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
