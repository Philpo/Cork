#include "ResourceManager.h"

int ResourceManager::meshId = 0;
int ResourceManager::passId = 0;
map<int, ITexture* const> ResourceManager::textures;
map<int, Mesh* const> ResourceManager::meshes;
map<int, IShader* const> ResourceManager::shaders;
map<int, IPass* const> ResourceManager::passes;
map<string, int> ResourceManager::loadedTextureFiles;
map<string, int> ResourceManager::loadedMeshFiles;
map<string, vector<int>> ResourceManager::loadedPassFiles;

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
  for (auto kvp : passes) {
    delete kvp.second;
  }

  textures.clear();
  meshes.clear();
  shaders.clear();
  passes.clear();

  loadedTextureFiles.clear();
  loadedMeshFiles.clear();
  loadedPassFiles.clear();

  meshId = 0;
  passId = 0;
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

IPass* const ResourceManager::getPass(int passId) {
  if (passes.find(passId) == passes.end()) {
    return nullptr;
  }
  return passes[passId];
}

void ResourceManager::loadTexture(string& type, string& textureFile, int& textureId) {
  if (loadedTextureFiles.find(textureFile) == loadedTextureFiles.end()) {
    ITexture* texture = nullptr;
    TextureInfo info(type, textureFile, texture);

    try {
      MessageHandler::forwardMessage(Message(LOAD_TEXTURE_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    }
    catch (exception&) {
      if (texture) {
        delete texture;
      }
      throw;
    }

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
    Mesh* mesh = new Mesh(ResourceManager::meshId, meshFile);

    try {
      MessageHandler::forwardMessage(Message(LOAD_MESH_MESSAGE, mesh, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    }
    catch (exception&) {
      delete mesh;
      throw;
    }

    loadedMeshFiles.insert(pair<string, int>(meshFile, mesh->getId()));
    meshes.insert(pair<int, Mesh* const>(mesh->getId(), mesh));
    meshId = mesh->getId();
    ResourceManager::meshId++;
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
    if (shader) {
      delete shader;
    }
    throw;
  }

  shaders.insert(pair<int, IShader* const>(info.shaderId, shader));
  shaderId = info.shaderId;
}

void ResourceManager::loadPasses(const string& passesFile, vector<IPass* const>& loadedPasses) {
  IPass* pass = nullptr;
  vector<int> passIndices;

  if (loadedPassFiles.find(passesFile) == loadedPassFiles.end()) {
    try {
      file<> file(passesFile.c_str());
      xml_document<> doc;
      doc.parse<0>(file.data());
      xml_node<>* rootNode = doc.first_node();

      for (xml_node<>* passNode = rootNode->first_node(); passNode; passNode = passNode->next_sibling()) {
        PassInfo info(passNode, pass);
        MessageHandler::forwardMessage(Message(LOAD_PASS_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));

        loadedPasses.push_back(pass);
        passes.insert(pair<int, IPass* const>(passId, pass));
        passIndices.push_back(passId++);
      }

      loadedPassFiles.insert(pair<string, vector<int>>(passesFile, passIndices));
    }
    catch (exception&) {
      if (pass) {
        delete pass;
      }
      for (auto index : passIndices) {
        delete passes[index];
        passes.erase(index);
      }
      loadedPassFiles.erase(passesFile);
      throw;
    }
  }
  else {
    for (auto pass : loadedPassFiles[passesFile]) {
      loadedPasses.push_back(passes[pass]);
    }
  }
}