#pragma once
#include "BinaryData.h"
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

void loadXMLMesh(const string& fileName, vector<BinaryData* const>& vertices, vector<int>& indices, vector<int>& textures, MeshMaterial& material);