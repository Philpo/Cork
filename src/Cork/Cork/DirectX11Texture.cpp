#include "DirectX11Texture.h"

DirectX11Texture::DirectX11Texture(int id, const std::string& type, ID3D11ShaderResourceView& texture) : id(id), type(type), texture(&texture) {}

DirectX11Texture::~DirectX11Texture() {
  if (texture) {
    texture->Release();
  }
}