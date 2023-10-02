#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace utils {
  void ReadFile(std::ifstream& inputStream, const std::string& path);
}
