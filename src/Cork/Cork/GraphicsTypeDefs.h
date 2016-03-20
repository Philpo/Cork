#pragma once
#include <string>
#include "TransformComponent.h"

const std::string BEGIN_FRAME_MESSAGE = "BeginFrameMessage";
const std::string SWAP_BUFFER_MESSAGE = "SwapBufferMessage";
const std::string SET_CONSTANT_BUFFER = "SetConstantBufferMessage";
const std::string SET_LIGHT = "SetLightMessage";
const std::string SET_CAMERA = "SetCameraMessage";
const std::string SET_SHADER = "SetShaderMessage";

const std::string LOAD_TEXTURE = "LoadTextureMessage";
const std::string LOAD_MESH = "LoadMeshMessage";
const std::string LOAD_SHADER = "LoadShaderMessage";

struct TextureInfo {
  TextureInfo(std::string& filePath, void* texture) : filePath(filePath), texture(texture) {}
  std::string filePath;
  void* texture;
};

struct ShaderInfo {
  ShaderInfo(const std::string& shaderFile, const std::string& name, const std::string& shaderModel, void* shader) :
    shaderId(-1), shaderFile(shaderFile), name(name), shaderModel(shaderModel), shader(shader) {}
  int shaderId;
  std::string shaderFile, name, shaderModel; 
  void* shader;
};

struct DrawInfo {
  int meshId;
  Transform transform;
};