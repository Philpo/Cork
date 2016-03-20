#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <string>

using namespace DirectX;

const std::string SET_INPUT_LAYOUT = "SetInputLayoutMessage";
const std::string LOAD_INPUT_LAYOUT = "LoadInputLayoutMessage";
const std::string CREATE_CONSTANT_BUFFER = "CreateConstantBufferMessage";

const int MAX_LIGHTS = 1;

struct InputLayoutInfo {
  InputLayoutInfo(int vertexShader, D3D11_INPUT_ELEMENT_DESC* layout, int numElements, void* inputLayout) : 
    layout(layout), vertexShader(vertexShader), numElements(numElements), inputLayout(inputLayout) {}
  D3D11_INPUT_ELEMENT_DESC* layout;
  int vertexShader, numElements;
  void* inputLayout;
};

struct LightStruct {
  LightStruct() : range(0.0f), exponent(0.0f), enabled(1) {
    ambient = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
    diffuse = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
    specular = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
    position = XMFLOAT3 { 0.0f, 0.0f, 0.0f };
    direction = XMFLOAT3 { 0.0f, 0.0f, 0.0f };
    attenuation = XMFLOAT3 { 0.0f, 0.0f, 0.0f };
  }

  XMFLOAT4 ambient;
  XMFLOAT4 diffuse;
  XMFLOAT4 specular;
  XMFLOAT3 position;
  float range;
  XMFLOAT3 direction;
  float exponent;
  XMFLOAT3 attenuation;
  int enabled;
  int type;
  XMFLOAT3 padding;
};

struct Material {
  Material() : specularPower(0.0f) {
    ambient = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
    diffuse = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
    specular = XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f };
  }

  XMFLOAT4 ambient, diffuse, specular;
  float specularPower;
};