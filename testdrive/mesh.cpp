#include "mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void model::Mesh::Setup(
  float* vertices,
  unsigned int verticesSize,
  unsigned int* indices,
  unsigned int indicesSize,
  const std::string& texturePath
) {
  // setup vao
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  // setup vbo
  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

  // setup ebo
  glGenBuffers(1, &_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

  // setup texture
  _SetupTexture(texturePath);

  // set vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3)); // color
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6)); // color
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void model::Mesh::_SetupTexture(const std::string& texturePath) {
  // activate texture unit
  glActiveTexture(GL_TEXTURE0);

  // generate texture
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

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
