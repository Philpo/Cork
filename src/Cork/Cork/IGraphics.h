#pragma once
#include "IComponent.h"
#include "ITexture.h"
#include "IShader.h"
#include "GraphicsTypeDefs.h"
#include "Mesh.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include <windows.h>

using namespace std;

class IGraphics : public IComponent {
public:
  virtual ~IGraphics() {}

  const std::string& getType() const override { return GRAPHICS_COMPONENT; }

  virtual void cleanup() = 0;
  virtual HRESULT loadTexture(const string& textureFile, ITexture*& texture) const = 0;
  virtual HRESULT loadMesh(const Mesh& mesh) = 0;
  virtual HRESULT loadShader(const string& shaderFile, const string& type, const string& shaderModel, IShader*& shader) const = 0;
private:
  virtual HRESULT initialise() = 0;
  virtual void setLight(Light light) = 0;
  virtual void setCamera(Camera camera) = 0;
  virtual void beginFrame() = 0;
  virtual void draw(DrawInfo data) = 0;
  virtual void swap() const = 0;
};