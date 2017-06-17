#pragma once
#include <string>
#include "ITexture.h"
#include "IShader.h"
#include "RapidXML\rapidxml.hpp"

using namespace rapidxml;

const std::size_t BEGIN_FRAME_MESSAGE = std::hash<std::string>{}("BeginFrameMessage");
const std::size_t BEGIN_PASS_MESSAGE = std::hash<std::string>{}("BeginPassMessage");
const std::size_t SWAP_BUFFER_MESSAGE = std::hash<std::string>{}("SwapBufferMessage");
const std::size_t SET_CONSTANT_BUFFER_MESSAGE = std::hash<std::string>{}("SetConstantBufferMessage");
const std::size_t SET_SHADER_MESSAGE = std::hash<std::string>{}("SetShaderMessage");

const std::size_t LOAD_TEXTURE_MESSAGE = std::hash<std::string>{}("LoadTextureMessage");
const std::size_t LOAD_MESH_MESSAGE = std::hash<std::string>{}("LoadMeshMessage");
const std::size_t LOAD_SHADER_MESSAGE = std::hash<std::string>{}("LoadShaderMessage");
const std::size_t LOAD_PASS_MESSAGE = std::hash<std::string>{}("LoadPassMessage");
const std::size_t CREATE_RENDER_TARGET_MESSAGE = std::hash<std::string>{}("CreateRenderTargetMessage");
const std::size_t CREATE_DEPTH_BUFFER_MESSAGE = std::hash<std::string>{}("CreateDepthBufferMessage");
const std::size_t CREATE_VIEWPORT_MESSAGE = std::hash<std::string>{}("CreateViewportMessage");

struct TextureInfo {
  TextureInfo(std::string& type, std::string& filePath, ITexture*& texture) : type(type), filePath(filePath), texture(texture) {}
  std::string type, filePath;
  ITexture*& texture;
};

struct ShaderInfo {
  ShaderInfo(const std::string& shaderFile, const std::string& name, const std::string& shaderModel, IShader*& shader) :
    shaderId(-1), shaderFile(shaderFile), name(name), shaderModel(shaderModel), shader(shader) {}
  int shaderId;
  std::string shaderFile, name, shaderModel; 
  IShader*& shader;
};

struct PassInfo {
  PassInfo(xml_node<>* passNode, IPass*& pass) : passNode(passNode), pass(pass) {}

  xml_node<>* passNode;
  IPass*& pass;
};

struct DrawInfo {
  int meshId, shaderId;
};

struct CreateInfo {
  int height, width, format, depthBufferFormat, textureViewFormat;
  std::string id;
  bool createTextureView, renderToBackBuffer;
};