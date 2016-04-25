#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <string>
#include <map>

using namespace DirectX;

const std::string SET_INPUT_LAYOUT_MESSAGE = "SetInputLayoutMessage";
const std::string LOAD_INPUT_LAYOUT_MESSAGE = "LoadInputLayoutMessage";
const std::string CREATE_CONSTANT_BUFFER_MESSAGE = "CreateConstantBufferMessage";
const std::string REGISTER_TEXTURE_REGISTERS_MESSAGE = "RegisterTextureRegistersMessage";

const int MAX_LIGHTS = 1;

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