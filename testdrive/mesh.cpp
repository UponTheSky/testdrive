#include "mesh.h"

void model::Mesh::Setup(float* vertices, unsigned int verticesSize) {
  // setup vao
  glGenVertexArrays(1, &_VAO);
  glGenBuffers(1, &_VBO);

  glBindVertexArray(_VAO);

  // setup vbo

  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

  // set vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
