#include "DirectX11Shader.h"

DirectX11Shader::~DirectX11Shader() {
  if (shader) {
    shader->Release();
  }
}