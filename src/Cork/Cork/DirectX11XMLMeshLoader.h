#pragma once
#include "DirectX11Vertex.h"
#include "DirectX11Graphics.h"
#include "ResourceManager.h"
#include "Utils.h"
#include "RapidXML\rapidxml.hpp"
#include "RapidXML\rapidxml_utils.hpp"
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace rapidxml;

void addVertices(xml_node<>* verticesNode, vector<IVertex* const>& vertices, int vertexSize);
void addIndices(xml_node<>* indicesNode, vector<int>& indices);
HRESULT addTextures(xml_node<>* texturesNode, vector<int>& textures);
HRESULT loadXMLMesh(const string& fileName, vector<IVertex* const>& vertices, vector<int>& indices, vector<int>& textures);