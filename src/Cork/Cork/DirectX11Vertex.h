#pragma once
#include "IVertex.h"
#include <directxmath.h>
#include <exception>
#include <sstream>

using namespace DirectX;

class DirectX11Vertex : public IVertex {
public:
  DirectX11Vertex(int sizeInBytes);
  ~DirectX11Vertex();

  char* const getData() const override { return buffer; }
  int getSizeInBytes() const override { return sizeInBytes; }

  void addFloat2(void* toAdd) override;
  void addFloat3(void* toAdd) override;
  void addFloat4(void* toAdd) override;
private:
  int sizeInBytes, currentBufferSize;
  char *buffer, *currentPosition;
};