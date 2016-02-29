#include "Mesh.h"

Mesh::Mesh(int id, const std::string& meshFile) : id(id) {
  // TODO add mesh loaders
  int fileExtensionStartIndex = meshFile.find(".");
  if (fileExtensionStartIndex != string::npos) {
    string fileExtension = meshFile.substr(fileExtensionStartIndex);
    if (meshFileLoaders.find(fileExtension) != meshFileLoaders.end()) {
      meshFileLoaders[fileExtension](meshFile, vertices, indices, textures);
    }
  }


}