#include "mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void model::Mesh::Setup(
  float* vertices,
  unsigned int verticesSize,
  unsigned int* indices,
  unsigned int indicesSize,
  const std::vector<const char*>& texturePaths
) {
  // setup vao
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  // setup vbo
  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

  // setup ebo
  // glGenBuffers(1, &_EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

  // setup texture
  for (size_t i = 0; i < texturePaths.size(); i++)
  {
    _SetupTexture(texturePaths[i], i);
  }

  // set vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3)); // normal
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6)); // texture
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void model::Mesh::BindTexture(size_t index) const {
  if (index == 0) {
    glActiveTexture(GL_TEXTURE0);
  } else {
    glActiveTexture(GL_TEXTURE1);
  }
    glBindTexture(GL_TEXTURE_2D, _textures[index]);
  }

void model::Mesh::_SetupTexture(const std::string& texturePath, size_t index) {
  if (texturePath.size() == 0) {
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }

  // activate texture unit
  if (index == 0) {
    glActiveTexture(GL_TEXTURE0);
  } else {
    glActiveTexture(GL_TEXTURE1);
  }

  // generate texture
  glGenTextures(1, &_textures[index]);
  glBindTexture(GL_TEXTURE_2D, _textures[index]);

  // set texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load image and combine with the texture object
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

  if (!data) {
    throw std::runtime_error("Reading the texture image has not been successful");
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}
