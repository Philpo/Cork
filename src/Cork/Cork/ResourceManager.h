#pragma once
#include "ServiceLocator.h"
#include "IGraphics.h"
#include "MessageHandler.h"
#include "Message.h"
#include <map>
#include <string>
#include "RapidXML\rapidxml.hpp"
#include "RapidXML\rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

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
  static IPass* const getPass(int passId);

  static void loadTexture(string& type, string& textureFile, int& textureId);
  static void loadMesh(string& meshFile, int& meshId);
  static void loadShader(const string& shaderFile, const string& name, const string& shaderModel, int& shaderId);
  static void loadPasses(const string& passesfile, vector<IPass* const>& loadedPasses);
private:
  static int meshId, passId;
  static map<int, ITexture* const> textures;
  static map<int, Mesh* const> meshes;
  static map<int, IShader* const> shaders;
  static map<int, IPass* const> passes;
  static map<string, int> loadedTextureFiles, loadedMeshFiles;
  static map<string, vector<int>> loadedPassFiles;
};