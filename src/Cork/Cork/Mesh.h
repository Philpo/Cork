#pragma once
#include <vector>
#include <map>
#include <functional>
#include <windows.h>
#include "BinaryData.h"
#include "Vector3.h"

using namespace std;

struct MeshMaterial {
  Vector3 ambient, diffuse, specular;
  float alpha, specularPower;
};

typedef function<void (const string&, vector<BinaryData* const>&, vector<int>&, vector<int>&, MeshMaterial&)> MeshLoadFunction;

class Mesh {
public:
  Mesh(int id, const string& meshFile);
  ~Mesh();

  int getId() const { return id; }
  const vector<BinaryData* const>& getVertices() const { return vertices; }
  const vector<int>& getIndices() const { return indices; }
  const vector<int>& getTextures() const { return textures; }
<<<<<<< HEAD
  const MeshMaterial getMaterial() const { return material; }
=======
  const MeshMaterial& getMaterial() const { return material; }
>>>>>>> 52a51f58ff3e8ee3cd3e848a451a444d40f4bcfc

  static void addMeshFileLoader(const string& fileExtension, MeshLoadFunction function);
private:
  int id;
  vector<BinaryData* const> vertices;
  vector<int> indices, textures;
  MeshMaterial material;
  static map<string, MeshLoadFunction> meshFileLoaders;
};