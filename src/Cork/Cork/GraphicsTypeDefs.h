#pragma once
#include <string>
#include "ITexture.h"
#include "IShader.h"
#include "RapidXML\rapidxml.hpp"

using namespace rapidxml;

const std::string BEGIN_FRAME_MESSAGE = "BeginFrameMessage";
const std::string BEGIN_PASS_MESSAGE = "BeginPassMessage";
const std::string SWAP_BUFFER_MESSAGE = "SwapBufferMessage";
const std::string SET_CONSTANT_BUFFER_MESSAGE = "SetConstantBufferMessage";
const std::string SET_SHADER_MESSAGE = "SetShaderMessage";

const std::string LOAD_TEXTURE_MESSAGE = "LoadTextureMessage";
const std::string LOAD_MESH_MESSAGE = "LoadMeshMessage";
const std::string LOAD_SHADER_MESSAGE = "LoadShaderMessage";
const std::string LOAD_PASS_MESSAGE = "LoadPassMessage";
const std::string CREATE_RENDER_TARGET_MESSAGE = "CreateRenderTargetMessage";
const std::string CREATE_DEPTH_BUFFER_MESSAGE = "CreateDepthBufferMessage";
const std::string CREATE_VIEWPORT_MESSAGE = "CreateViewportMessage";

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