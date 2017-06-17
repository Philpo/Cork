#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <string>
#include <map>

using namespace DirectX;

const std::size_t SET_INPUT_LAYOUT_MESSAGE = std::hash<std::string>{}("SetInputLayoutMessage");
const std::size_t LOAD_INPUT_LAYOUT_MESSAGE = std::hash<std::string>{}("LoadInputLayoutMessage");
const std::size_t CREATE_CONSTANT_BUFFER_MESSAGE = std::hash<std::string>{}("CreateConstantBufferMessage");
const std::size_t REGISTER_TEXTURE_REGISTERS_MESSAGE = std::hash<std::string>{}("RegisterTextureRegistersMessage");

struct InputLayoutInfo {
  InputLayoutInfo(int vertexShader, D3D11_INPUT_ELEMENT_DESC* layout, int numElements, ID3D11InputLayout*& inputLayout) :
    layout(layout), vertexShader(vertexShader), numElements(numElements), inputLayout(inputLayout) {}
  D3D11_INPUT_ELEMENT_DESC* layout;
  int vertexShader, numElements;
  ID3D11InputLayout*& inputLayout;
};

struct ShaderTexRegisterInfo {
  ShaderTexRegisterInfo(int shaderId, const map<std::string, int>& textureRegisters) : shaderId(shaderId), textureRegisters(textureRegisters) {}
  int shaderId;
  map<std::string, int> textureRegisters;
};