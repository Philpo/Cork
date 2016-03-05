#pragma once
#include <vector>
#include <map>
#include <functional>
#include <windows.h>
#include "IVertex.h"

using namespace std;

typedef function<HRESULT (const string&, vector<IVertex* const>&, vector<int>&, vector<int>&)> meshLoadFunction;

class Mesh {
public:
  Mesh(int id, const string& meshFile);
  ~Mesh();

  inline int getId() const { return id; }
  inline const vector<IVertex* const>& getVertices() const { return vertices; }
  inline const vector<int>& getIndices() const { return indices; }
  inline const vector<int>& getTextures() const { return textures; }

  static void addMeshFileLoader(const string& fileExtension, meshLoadFunction function);
private:
  int id;
  vector<IVertex* const> vertices;
  vector<int> indices, textures;
  static map<string, meshLoadFunction> meshFileLoaders;
};