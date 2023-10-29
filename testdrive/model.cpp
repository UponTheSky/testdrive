#include "model.h"

#include <iostream>
using namespace model;

void Model::Draw(const Shader& shader) const
{
  for (const auto& mesh : mMeshes)
  {
    mesh.Draw(shader);
  }
}

void Model::LoadModel(const std::string& path)
{
  Assimp::Importer import;
  const aiScene* scene = import.ReadFile(
    path,
    aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
  );

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    throw std::logic_error(std::string("ERROR::ASSIMP::") + import.GetErrorString());
  }

  mDirectory = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
  // array as a double pointer(**), not a container
  for (size_t i = 0; i < node->mNumMeshes; i++)
  {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    mMeshes.push_back(ProcessMesh(mesh, scene));
  }

  for (size_t i = 0; i < node->mNumChildren; i++)
  {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // vertices
  for (size_t i = 0; i < mesh->mNumVertices; i++)
  {
    glm::vec3 vector(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
    glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

    glm::vec2 texCoords;
    if (mesh->mTextureCoords[0])
    {
      texCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
    }
    vertices.push_back({ vector, normal, texCoords });
  }

  // indices
  for (size_t i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  // materials
  if (mesh->mMaterialIndex >= 0)
  {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
  std::vector<Texture> textures;
  for (size_t i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;
    mat->GetTexture(type, i, &str);
    const char* path = str.C_Str();
    if (mLoadedTexturesList.find(path) == mLoadedTexturesList.end())
    {
      mLoadedTexturesList[path] = {TextureFromFile(path, mDirectory), typeName, path};
    }

    textures.push_back(mLoadedTexturesList[path]);
  }

  return textures;
}

unsigned int Model::TextureFromFile(const std::string& path, const std::string& directory, bool gamma)
{
  // load image and combine with the texture object
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char* data = stbi_load((directory + "/" + path).c_str(), &width, &height, &nrChannels, 0);

  if (!data) {
    throw std::runtime_error("Reading the texture image has not been successful");
  }
  GLenum format = GL_RED;

  if (nrChannels == 3)
  {
    format = GL_RGB;
  }
  else if (nrChannels == 4)
  {
    format = GL_RGBA;
  }

  // generate texture
  unsigned int id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  // set texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  glBindTexture(GL_TEXTURE_2D, 0);

  return id;
}
