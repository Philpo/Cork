#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <string>

using namespace DirectX;

const std::string SET_INPUT_LAYOUT = "SetInputLayoutMessage";

const int MAX_LIGHTS = 1;
const int cb_size = 3;

inline const float convertDegreesToRadians(const float angleInDegrees) {
  return (angleInDegrees * XM_PI) / 180;
}

struct SimpleVertex {
  XMFLOAT3 Pos;
  XMFLOAT3 normal;
  XMFLOAT3 tangent;
  XMFLOAT2 texC;
};

struct LightStruct {
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
  Material() { ZeroMemory(this, sizeof(this)); }
  XMFLOAT4 ambient, diffuse, specular;
  float specularPower;
};

struct ConstantBuffer {
  XMMATRIX mWorld;
  XMMATRIX mView;
  XMMATRIX mProjection;
  LightStruct lights[MAX_LIGHTS];
  Material material;
  XMFLOAT3 eyePositionW;
  int enableTexturing;
  int enableSpecularMapping;
  int enableBumpMapping;
  int enableClipTesting;
  float fogStart;
  float fogRange;
  XMFLOAT2 padding;
  XMFLOAT4 fogColour;
};

struct NewCB {
  NewCB() : data(new byte[sizeof(XMMATRIX) * 3]) {}
  void* data;
};