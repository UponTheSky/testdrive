#include "mesh.h"

void model::Mesh::Setup(
  float* vertices,
  unsigned int verticesSize,
  unsigned int* indices,
  unsigned int indicesSize
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

  // set vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3)); // color
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}
