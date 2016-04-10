#pragma once
#include <vector>

class IPass {
public:
  virtual ~IPass() {}

  virtual int getNumRenderTargets() const = 0;
  virtual const std::vector<int>& getRenderTargets() const = 0;
  virtual int getDepthBuffer() const = 0;
  virtual int getViewPort() const = 0;
  virtual void* const getRenderTargetBindTargets() const = 0;
  virtual void* const getDepthBufferBindTargets() const = 0;

  virtual void setRenderTargets(const std::vector<int>& renderTargets) = 0;
  virtual void setDepthBuffer(int depthBuffer) = 0;
  virtual void setViewport(int viewport) = 0;
  virtual void setRenderTargetBindTargets(void* const bindTargets) = 0;
  virtual void setDepthBufferBindTargets(void* const bindTargets) = 0;
};