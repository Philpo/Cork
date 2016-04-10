#pragma once
#include <string>

const std::string BEGIN_FRAME_MESSAGE = "BeginFrameMessage";
const std::string BEGIN_PASS_MESSAGE = "BeginPassMessage";
const std::string SWAP_BUFFER_MESSAGE = "SwapBufferMessage";
const std::string SET_CONSTANT_BUFFER_MESSAGE = "SetConstantBufferMessage";
const std::string SET_SHADER_MESSAGE = "SetShaderMessage";

const std::string LOAD_TEXTURE_MESSAGE = "LoadTextureMessage";
const std::string LOAD_MESH_MESSAGE = "LoadMeshMessage";
const std::string LOAD_SHADER_MESSAGE = "LoadShaderMessage";
const std::string CREATE_RENDER_TARGET_MESSAGE = "CreateRenderTargetMessage";
const std::string CREATE_DEPTH_BUFFER_MESSAGE = "CreateDepthBufferMessage";
const std::string CREATE_VIEWPORT_MESSAGE = "CreateViewportMessage";

struct TextureInfo {
  TextureInfo(std::string& type, std::string& filePath, void* texture) : type(type), filePath(filePath), texture(texture) {}
  std::string type, filePath;
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
  int meshId, shaderId;
};

struct CreateInfo {
  int height, width, id;
  bool createTextureView, renderToBackBuffer;
};