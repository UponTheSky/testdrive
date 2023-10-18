#pragma once

#include "mesh.h"

class Light : public model::Mesh {
  public:
    Light(const glm::mat4& trans, const glm::vec3& color, const glm::vec3& position)
    : Mesh(trans), _color(color), _position(position) {}

    glm::vec3 GetColor() const { return _color; }
    glm::vec3 GetPosition() const { return _position; }

  private:
    glm::vec3 _color, _position;
};
