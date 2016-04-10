#pragma once
#include "IPass.h"
#include <map>

using namespace std;

class DirectX11Pass : public IPass {
public:
  DirectX11Pass();
  ~DirectX11Pass() {}

  int getNumRenderTargets() const override { return renderTargets.size(); }
  const std::vector<int>& getRenderTargets() const override { return renderTargets; }
  int getDepthBuffer() const override { return depthBuffer; }
  int getViewPort() const override { return viewport; }
  void* const getRenderTargetBindTargets() const override { return (void*) &renderTargetBindTargets; }
  void* const getDepthBufferBindTargets() const override { return (void*) &depthBufferBindTargets; }

  void setRenderTargets(const vector<int>& renderTargets) override { this->renderTargets = renderTargets; }
  void setDepthBuffer(int depthBuffer) override { this->depthBuffer = depthBuffer; }
  void setViewport(int viewport) override { this->viewport = viewport; }
  void setRenderTargetBindTargets(void* const bindTargets) override { this->renderTargetBindTargets = *(map<int, int>*) bindTargets; }
  void setDepthBufferBindTargets(void* const bindTargets) override { this->depthBufferBindTargets = *(map<int, int>*) bindTargets; }
private:
  int depthBuffer, viewport;
  vector<int> renderTargets;
  map<int, int> renderTargetBindTargets, depthBufferBindTargets;
};