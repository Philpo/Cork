#pragma once
#include <vector>
#include <string>

class IPass {
public:
  virtual ~IPass() {}

  virtual int getNumRenderTargets() const = 0;
  virtual const std::vector<std::string>& getRenderTargets() const = 0;
  virtual const std::string& getDepthBuffer() const = 0;
  virtual const std::string& getViewPort() const = 0;
  virtual void* const getRenderTargetBindTargets() const = 0;
  virtual void* const getDepthBufferBindTargets() const = 0;

  virtual void setRenderTargets(const std::vector<std::string>& renderTargets) = 0;
  virtual void setDepthBuffer(std::string& depthBuffer) = 0;
  virtual void setViewport(std::string& viewport) = 0;
  virtual void setRenderTargetBindTargets(void* const bindTargets) = 0;
  virtual void setDepthBufferBindTargets(void* const bindTargets) = 0;
};