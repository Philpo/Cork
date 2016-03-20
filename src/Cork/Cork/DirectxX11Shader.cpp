#include "DirectX11Shader.h"

DirectX11Shader::~DirectX11Shader() {
  if (shader) {
    ((ID3D11DeviceChild*) shader)->Release();
  }
}