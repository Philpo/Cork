#include "ResourceManager.h"

int ResourceManager::meshId = 0;
map<int, ITexture* const> ResourceManager::textures;
map<int, Mesh* const> ResourceManager::meshes;
map<string, int> ResourceManager::loadedTextureFiles;
map<string, int> ResourceManager::loadedMeshFiles;

void ResourceManager::cleanup() {
  for (auto kvp : textures) {
    delete kvp.second;
  }
  for (auto kvp : meshes) {
    delete kvp.second;
  }
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

HRESULT ResourceManager::loadTexture(string& textureFile, int& textureId) {
  HRESULT hr;

  if (loadedTextureFiles.find(textureFile) == loadedTextureFiles.end()) {
    IGraphics* graphics = (IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT);
    ITexture* texture;
    hr = graphics->loadTexture(textureFile, texture);
    
    if (FAILED(hr)) {
      return hr;
    }

    loadedTextureFiles.insert(pair<string, int>(textureFile, texture->getId()));
    textures.insert(pair<int, ITexture* const>(texture->getId(), texture));
    textureId = texture->getId();
  }
  else {
    textureId = loadedTextureFiles[textureFile];
  }

  return S_OK;
}

HRESULT ResourceManager::loadMesh(string& meshFile, int& meshId) {
  HRESULT hr;

  if (loadedMeshFiles.find(meshFile) == loadedMeshFiles.end()) {
    IGraphics* graphics = (IGraphics*) ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT);
    Mesh* mesh = new Mesh(ResourceManager::meshId++, meshFile);
    hr = graphics->loadMesh(*mesh);

    if (FAILED(hr)) {
      delete mesh;
      return hr;
    }

    loadedMeshFiles.insert(pair<string, int>(meshFile, mesh->getId()));
    meshes.insert(pair<int, Mesh* const>(mesh->getId(), mesh));
    meshId = mesh->getId();
  }
  else {
    meshId = loadedMeshFiles[meshFile];
  }

  return S_OK;
}