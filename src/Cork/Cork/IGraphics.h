#pragma once
#include "IComponent.h"
#include "ITexture.h"
#include "IShader.h"
#include "IPass.h"
#include "GraphicsTypeDefs.h"
#include "Mesh.h"
#include <windows.h>

using namespace std;

extern const bool UNIT_TESTS;

class IGraphics : public IComponent {
public:
  virtual ~IGraphics() {}

  std::size_t getType() const override { return GRAPHICS_COMPONENT; }

  virtual void cleanup() = 0;
private:
  virtual HRESULT initialise() = 0;
  virtual void loadTexture(TextureInfo& info) const = 0;
  virtual void loadMesh(const Mesh& mesh) = 0;
  virtual void loadShader(ShaderInfo& info) = 0;
  virtual void loadPass(PassInfo& info) = 0;
  virtual void createRenderTarget(CreateInfo& info) = 0;
  virtual void createDepthBuffer(CreateInfo& info) = 0;
  virtual void createViewport(CreateInfo& info) = 0;
  virtual void setShader(int shaderId) = 0;
  virtual void beginFrame() = 0;
  virtual void beginPass(const IPass& pass) = 0;
  virtual void draw(DrawInfo data) = 0;
  virtual void swap() const = 0;
};