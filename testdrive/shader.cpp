#include "shader.h"

void Shader::Build(
  const std::string& vertexShaderPath,
  const std::string& fragmentShaderPath
) {
  // create the program and the shaders
  _id = glCreateProgram();
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  try {
    // build shaders
    _BuildShader(vertexShaderPath, vertexShader);
    _BuildShader(fragmentShaderPath, fragmentShader);

    // link the shaders to the program
    _LinkShaders(vertexShader, fragmentShader);

  } catch (const std::runtime_error e) {
    glDeleteProgram(_id);
    _id = 0;
    std::cerr << e.what() << std::endl;
  }

  // retrive the resources
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::_BuildShader(const std::string& path, const unsigned int& shader) {
  // read shader source file(as a C string)
  std::ifstream shaderFile;
  utils::ReadFile(shaderFile, path);

  std::ostringstream tempStream;
  tempStream << shaderFile.rdbuf();
  shaderFile.close();

  const std::string shaderSource = tempStream.str();
  const char* shaderSourceCString = shaderSource.c_str();

  // connect the shader to the shader source code and compile it
  glShaderSource(shader, 1, &shaderSourceCString, nullptr);
  glCompileShader(shader);

  // check whether the compilation is successful or not
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
  }
}

void Shader::_LinkShaders(const unsigned int& vertexShader, const unsigned int& fragmentShader) {
  glAttachShader(_id, vertexShader);
  glAttachShader(_id, fragmentShader);
  glLinkProgram(_id);

  int success;
  char infoLog[512];
  glGetProgramiv(_id, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(_id, 512, nullptr, infoLog);
    throw std::runtime_error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
  }
}

void Shader::Use() const {
  if (_id == 0) {
    throw std::logic_error("The shader has not been built yet");
  }
  _isUsed = true;
  glUseProgram(_id);
}


void Shader::SetUniformBool(const std::string& name, bool value) const {
  _CheckCurrentlyUsed();
  glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void Shader::SetUniformInt(const std::string& name, int value) const {
  _CheckCurrentlyUsed();
  glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::SetUniformFloat(const std::string& name, float value) const {
  _CheckCurrentlyUsed();
  glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value) const {
  _CheckCurrentlyUsed();
  glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value) const {
  _CheckCurrentlyUsed();
  glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value) const {
  _CheckCurrentlyUsed();
  glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
