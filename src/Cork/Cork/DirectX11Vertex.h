#pragma once
#include "IVertex.h"
#include <directxmath.h>

using namespace DirectX;

class DirectX11Vertex : public IVertex {
public:
  DirectX11Vertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT3 tangent, XMFLOAT2 texCoords);
  ~DirectX11Vertex() {}

  void* getPosition() const override { return (void*) &position; }
  void* getNormal() const override { return (void*) &normal; }
  void* getTangent() const override { return (void*) &tangent; }
  void* getTexCoords() const override { return (void*) &texCoords; }
private:
  XMFLOAT3 position, normal, tangent;
  XMFLOAT2 texCoords;
};