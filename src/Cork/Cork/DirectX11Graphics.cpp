#include "DirectX11Graphics.h"

unique_ptr<DirectX11Graphics> DirectX11Graphics::instance;

DirectX11Graphics::DirectX11Graphics() {}

const DirectX11Graphics& DirectX11Graphics::getGraphics() {
  if (!instance) {
    instance.reset(new DirectX11Graphics());
  }
  return *instance;
}

void DirectX11Graphics::receiveMessage(IMessage& message) {

}

void DirectX11Graphics::cleanup() {

}

HRESULT DirectX11Graphics::loadTexture(const string& textureFile, ITexture*& texuture) const {
  return S_OK;
}

HRESULT DirectX11Graphics::loadMesh(const Mesh& mesh) {
  return S_OK;
}

HRESULT DirectX11Graphics::initialise() {
  return S_OK;
}

void DirectX11Graphics::draw(int meshId) const {

}

void DirectX11Graphics::swap() const {

}