#include "DirectX11Texture.h"

DirectX11Texture::DirectX11Texture(int id, ID3D11ShaderResourceView& texture) : id(id), texture(&texture) {}

DirectX11Texture::~DirectX11Texture() {
  if (texture) {
    texture->Release();
  }
}