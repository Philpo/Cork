#pragma once
#include "ITexture.h"
#include <d3d11_1.h>

class DirectX11Texture : public ITexture {
public:
  DirectX11Texture(int id, const std::string& type, ID3D11ShaderResourceView& texture);
  ~DirectX11Texture();

  int getId() const override { return id; }
  const std::string& getType() const override { return type; }
  void* const getTexture() const override { return texture; }
private:
  int id;
  std::string type;
  ID3D11ShaderResourceView* texture;
};