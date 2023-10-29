#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <map>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "stb_image.h"

#include "shader.h"
#include "mesh.h"

namespace model {
  class Model
  {
    public:
      Model(const std::string& path) { LoadModel(path); }
      void Draw(const Shader& shader) const;

    private:
      std::vector<Mesh> mMeshes;
      std::string mDirectory;
      std::map<std::string, Texture> mLoadedTexturesList;

      void LoadModel(const std::string& path);
      void ProcessNode(aiNode* node, const aiScene* scene);
      Mesh ProcessMesh(aiMesh *mesh, const aiScene* scene);
      std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

      unsigned int TextureFromFile(const std::string& path, const std::string& directory, bool gamma = false);
  };
};
