#include "Mesh.h"

map<string, meshLoadFunction> Mesh::meshFileLoaders;

Mesh::Mesh(int id, const std::string& meshFile) : id(id) {
  int fileExtensionStartIndex = meshFile.rfind(".");
  if (fileExtensionStartIndex != string::npos) {
    string fileExtension = meshFile.substr(fileExtensionStartIndex);
    if (meshFileLoaders.find(fileExtension) != meshFileLoaders.end()) {
      meshFileLoaders[fileExtension](meshFile, vertices, indices, textures, material);
    }
  }
}

Mesh::~Mesh() {
  for (auto vertex : vertices) {
    delete vertex;
  }
}

void Mesh::addMeshFileLoader(const string& fileExtension, meshLoadFunction function) {
  if (meshFileLoaders.find(fileExtension) == meshFileLoaders.end()) {
    meshFileLoaders.insert(pair<string, meshLoadFunction>(fileExtension, function));
  }
}