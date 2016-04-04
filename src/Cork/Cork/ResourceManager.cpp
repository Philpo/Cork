#include "ResourceManager.h"

int ResourceManager::meshId = 0;
map<int, ITexture* const> ResourceManager::textures;
map<int, Mesh* const> ResourceManager::meshes;
map<int, IShader* const> ResourceManager::shaders;
map<string, int> ResourceManager::loadedTextureFiles;
map<string, int> ResourceManager::loadedMeshFiles;

void ResourceManager::cleanup() {
  for (auto kvp : textures) {
    delete kvp.second;
  }
  for (auto kvp : meshes) {
    delete kvp.second;
  }
  for (auto kvp : shaders) {
    delete kvp.second;
  }
  textures.clear();
  meshes.clear();
  shaders.clear();
}

ITexture* const ResourceManager::getTexture(int textureId) {
  if (textures.find(textureId) == textures.end()) {
    return nullptr;
  }
  return textures[textureId];
}

Mesh* const ResourceManager::getMesh(int meshId) {
  if (meshes.find(meshId) == meshes.end()) {
    return nullptr;
  }
  return meshes[meshId];
}

IShader* const ResourceManager::getShader(int shaderId) {
  if (shaders.find(shaderId) == shaders.end()) {
    return nullptr;
  }
  return shaders[shaderId];
}

void ResourceManager::loadTexture(string& type, string& textureFile, int& textureId) {
  if (loadedTextureFiles.find(textureFile) == loadedTextureFiles.end()) {
    ITexture* texture = nullptr;
    TextureInfo info(type, textureFile, texture);

    try {
      MessageHandler::forwardMessage(Message(LOAD_TEXTURE_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    }
    catch (exception&) {
      throw;
    }

    texture = (ITexture*) info.texture;

    loadedTextureFiles.insert(pair<string, int>(textureFile, texture->getId()));
    textures.insert(pair<int, ITexture* const>(texture->getId(), texture));
    textureId = texture->getId();
  }
  else {
    textureId = loadedTextureFiles[textureFile];
  }
}

void ResourceManager::loadMesh(string& meshFile, int& meshId) {
  if (loadedMeshFiles.find(meshFile) == loadedMeshFiles.end()) {
    Mesh* mesh = new Mesh(ResourceManager::meshId++, meshFile);

    try {
      MessageHandler::forwardMessage(Message(LOAD_MESH_MESSAGE, mesh, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    }
    catch (exception&) {
      throw;
    }

    loadedMeshFiles.insert(pair<string, int>(meshFile, mesh->getId()));
    meshes.insert(pair<int, Mesh* const>(mesh->getId(), mesh));
    meshId = mesh->getId();
  }
  else {
    meshId = loadedMeshFiles[meshFile];
  }
}

void ResourceManager::loadShader(const string& shaderFile, const string& name, const string& shaderModel, int& shaderId) {
  IShader* shader = nullptr;
  ShaderInfo info(shaderFile, name, shaderModel, shader);

  try {
    MessageHandler::forwardMessage(Message(LOAD_SHADER_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
  }
  catch (exception&) {
    throw;
  }

  shader = (IShader*) info.shader;

  shaders.insert(pair<int, IShader* const>(info.shaderId, shader));
  shaderId = info.shaderId;
}