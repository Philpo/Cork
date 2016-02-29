#pragma once
#include "ITexture.h"
#include <d3d11_1.h>

class DirectX11Texture : public ITexture {
public:
  DirectX11Texture(int id, ID3D11ShaderResourceView& texture);
  ~DirectX11Texture() {}

  int getId() const override { return id; }
  void* getTexture() const override { return texture; }
private:
  int id;
  ID3D11ShaderResourceView* texture;
};