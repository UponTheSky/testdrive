#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>

#include "utils.h"

class Shader {
  public:
    Shader() = default;

    void Use() const;

    void Build(
      const std::string& vertexShaderPath,
      const std::string& fragmentShaderPath
    );

  private:
    unsigned int _id;
    void _BuildShader(const std::string& path, const unsigned int& shader);
    void _LinkShaders(const unsigned int& vertexShader, const unsigned int& fragmentShader);
};
