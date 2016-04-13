#pragma once
#include "IShader.h"
#include <d3d11.h>

class DirectX11Shader : public IShader {
public:
  DirectX11Shader() : shader(nullptr), type("") {}
  ~DirectX11Shader();

  void* const getShader() const override { return shader; }
  const std::string& getType() const override { return type; }

  void setShader(void* const shader) override { this->shader = (ID3D11DeviceChild*) shader; }
  void setType(const std::string& type) override { this->type = type; }
private:
  ID3D11DeviceChild* shader;
  std::string type;
};