#include "utils.h"

void utils::ReadFile(std::ifstream& inputStream, const std::string& path) {
  std::filesystem::path fsPath(path);
  inputStream.open(fsPath);

  if (!inputStream) {
    inputStream.close();
    throw std::runtime_error("Could not read the shader file");
  }
}
