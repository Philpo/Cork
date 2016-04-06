#pragma once
#include "IComponent.h"
#include "ITexture.h"
#include "IShader.h"
#include "GraphicsTypeDefs.h"
#include "Mesh.h"
#include "GameObject.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include <windows.h>

using namespace std;

class IGraphics : public IComponent {
public:
  virtual ~IGraphics() {}

  const std::string& getType() const override { return GRAPHICS_COMPONENT; }

  virtual void cleanup() = 0;
private:
  virtual HRESULT initialise() = 0;
  virtual void loadTexture(TextureInfo& info) const = 0;
  virtual void loadMesh(const Mesh& mesh) = 0;
  virtual void loadShader(ShaderInfo& info) = 0;
  virtual void setLight(GameObject* const light) = 0;
  virtual void setCamera(GameObject* const camera) = 0;
  virtual void setShader(int shaderId) = 0;
  virtual void beginFrame() = 0;
  virtual void draw(DrawInfo data) = 0;
  virtual void swap() const = 0;
};