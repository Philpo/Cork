#pragma once
#include "Mesh.h"
#include "ITexture.h"
#include "ServiceLocator.h"
#include "IGraphics.h"
#include "MessageHandler.h"
#include "Message.h"
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
  static IShader* const getShader(int shaderId);

  static void loadTexture(string& textureFile, int& textureId);
  static void loadMesh(string& meshFile, int& meshId);
  static void loadShader(const string& shaderFile, const string& name, const string& shaderModel, int& shaderId);
private:
  static int meshId;
  static map<int, ITexture* const> textures;
  static map<int, Mesh* const> meshes;
  static map<int, IShader* const> shaders;
  static map<string, int> loadedTextureFiles, loadedMeshFiles;
};