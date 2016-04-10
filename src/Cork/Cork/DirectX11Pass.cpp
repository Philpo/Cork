#include "DirectX11Pass.h"

DirectX11Pass::DirectX11Pass() : depthBuffer(0), viewport(0) {
  renderTargets = { 0 };
}