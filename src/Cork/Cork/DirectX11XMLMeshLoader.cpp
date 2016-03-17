#include "DirectX11XMLMeshLoader.h"

void addVertices(xml_node<>* verticesNode, vector<BinaryData* const>& vertices, int vertexSize);
void addIndices(xml_node<>* indicesNode, vector<int>& indices);
HRESULT addTextures(xml_node<>* texturesNode, vector<int>& textures);
void addMaterial(xml_node<>* materialNode, MeshMaterial& material);

HRESULT loadXMLMesh(const string& fileName, vector<BinaryData* const>& vertices, vector<int>& indices, vector<int>& textures, MeshMaterial& material) {
  HRESULT hr;

  try {
    file<> meshFile(fileName.c_str());
    xml_document<> doc;
    doc.parse<0>(meshFile.data());
    xml_node<>* rootNode = doc.first_node();

    int numVertices = convertStringToNumber<int>(rootNode->first_attribute("num_vertices")->value());
    int numIndices = convertStringToNumber<int>(rootNode->first_attribute("num_indices")->value());
    int numTextures = convertStringToNumber<int>(rootNode->first_attribute("num_textures")->value());
    int vertexSize = convertStringToNumber<int>(rootNode->first_attribute("vertex_size_in_bytes")->value());

    vertices.resize(numVertices);
    indices.resize(numIndices);
    textures.resize(numTextures);

    addVertices(rootNode->first_node("vertices"), vertices, vertexSize);
    addIndices(rootNode->first_node("indices"), indices);
    hr = addTextures(rootNode->first_node("textures"), textures);

    if (FAILED(hr)) {
      return hr;
    }

    addMaterial(rootNode->first_node("material"), material);
  }
  catch (parse_error& e) {
    throw;
  }

  return S_OK;
}

void addVertices(xml_node<>* verticesNode, vector<BinaryData* const>& vertices, int vertexSize) {
  int currentVertex = 0;

  for (xml_node<>* vertexNode = verticesNode->first_node(); vertexNode; vertexNode = vertexNode->next_sibling()) {
    BinaryData* vertex = new BinaryData(vertexSize);

    for (xml_node<>* vertexData = vertexNode->first_node(); vertexData; vertexData = vertexData->next_sibling()) {
      int vectorSize = convertStringToNumber<int>(vertexData->first_attribute("num_attributes")->value());

      if (vectorSize == 2) {
        XMFLOAT2 vector;
        xml_attribute<>* attr = vertexData->first_attribute()->next_attribute();

        vector.x = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.y = convertStringToNumber<float>(attr->value());

        vertex->addData(vertexData->name(), vector);
      }
      else if (vectorSize == 3) {
        XMFLOAT3 vector;
        xml_attribute<>* attr = vertexData->first_attribute()->next_attribute();

        vector.x = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.y = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.z = convertStringToNumber<float>(attr->value());

        vertex->addData(vertexData->name(), vector);
      }
      else if (vectorSize == 4) {
        XMFLOAT4 vector;
        xml_attribute<>* attr = vertexData->first_attribute()->next_attribute();

        vector.x = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.y = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.z = convertStringToNumber<float>(attr->value());
        attr = attr->next_attribute();
        vector.w = convertStringToNumber<float>(attr->value());

        vertex->addData(vertexData->name(), vector);
      }
    }

    vertices[currentVertex++] = vertex;
  }
}

void addIndices(xml_node<>* indicesNode, vector<int>& indices) {
  int currentIndex = 0;

  for (xml_node<>* indexNode = indicesNode->first_node(); indexNode; indexNode = indexNode->next_sibling()) {
    int index = convertStringToNumber<int>(indexNode->first_node()->value());
    indices[currentIndex++] = index;
  }
}

HRESULT addTextures(xml_node<>* texturesNode, vector<int>& textures) {
  int currentTexture = 0;
  HRESULT hr;

  for (xml_node<>* textureNode = texturesNode->first_node(); textureNode; textureNode = textureNode->next_sibling()) {
    string textureFile = textureNode->first_attribute()->value();
    int textureId;

    hr = ResourceManager::loadTexture(textureFile, textureId);

    if (FAILED(hr)) {
      return hr;
    }

    textures[currentTexture++] = textureId;
  }

  return S_OK;
}

void addMaterial(xml_node<>* materialNode, MeshMaterial& material) {
  material.alpha = convertStringToNumber<float>(materialNode->first_attribute("a")->value());

  xml_node<>* component = materialNode->first_node("ambient");
  material.ambient.setX(convertStringToNumber<float>(component->first_attribute("r")->value()));
  material.ambient.setY(convertStringToNumber<float>(component->first_attribute("g")->value()));
  material.ambient.setZ(convertStringToNumber<float>(component->first_attribute("b")->value()));

  component = materialNode->first_node("diffuse");
  material.diffuse.setX(convertStringToNumber<float>(component->first_attribute("r")->value()));
  material.diffuse.setY(convertStringToNumber<float>(component->first_attribute("g")->value()));
  material.diffuse.setZ(convertStringToNumber<float>(component->first_attribute("b")->value()));

  component = materialNode->first_node("specular");
  material.specular.setX(convertStringToNumber<float>(component->first_attribute("r")->value()));
  material.specular.setY(convertStringToNumber<float>(component->first_attribute("g")->value()));
  material.specular.setZ(convertStringToNumber<float>(component->first_attribute("b")->value()));
  material.specularPower = convertStringToNumber<float>(component->first_attribute("power")->value());
}