#pragma once
#include "Mesh.h"
#include "ITexture.h"
#include "ServiceLocator.h"
#include "IGraphics.h"
#include <map>
#include <string>

using namespace std;

class ResourceManager {
public:
  ResourceManager() = delete;
  ResourceManager(ResourceManager& toCopy) = delete;
  ~ResourceManager() {}

  ResourceManager& operator=(ResourceManager rhs) = delete;

  static void cleanup();

  static ITexture* const getTexture(int textureId);
  static Mesh* const getMesh(int meshId);

  static HRESULT loadTexture(string& textureFile, int& textureId);
  static HRESULT loadMesh(string& meshFile, int& meshId);
private:
  static int meshId;
  static map<int, ITexture* const> textures;
  static map<int, Mesh* const> meshes;
  static map<string, int> loadedTextureFiles, loadedMeshFiles;
};