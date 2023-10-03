#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"

class Shader {
  public:
    Shader() = default;

    void Use() const;

    void Build(
      const std::string& vertexShaderPath,
      const std::string& fragmentShaderPath
    );

    void SetUniformBool(const std::string& name, bool value) const;
    void SetUniformInt(const std::string& name, int value) const;
    void SetUniformFloat(const std::string& name, float value) const;
    void SetUniformVec3(const std::string& name, const glm::vec3& value) const;
    void SetUniformVec4(const std::string& name, const glm::vec4& value) const;
    void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

  private:
    unsigned int _id;
    mutable bool _isUsed = false;

    void _CheckCurrentlyUsed() const {
      if (!_isUsed) {
        throw std::logic_error("The shader is not currently used");
      }
    }
    void _BuildShader(const std::string& path, const unsigned int& shader);
    void _LinkShaders(const unsigned int& vertexShader, const unsigned int& fragmentShader);
};
