#pragma once
#include "IComponent.h"
#include "ITexture.h"
#include "Mesh.h"
#include <windows.h>

class IGraphics : public IComponent {
public:
  virtual ~IGraphics();

  virtual void cleanup() = 0;
  virtual HRESULT loadTexture(const std::string& textureFile, ITexture*& texture) const = 0;
  virtual HRESULT loadMesh(const Mesh& mesh) = 0;
  const std::string& getType() const override { return GRAPHICS_COMPONENT; }
private:
  virtual HRESULT initialise() = 0;
  virtual void draw(int meshId) const = 0;
  virtual void swap() const = 0;
};