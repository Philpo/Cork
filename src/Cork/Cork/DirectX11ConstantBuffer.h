#pragma once
#include "IConstantBuffer.h"
#include "DirectX11TypeDefs.h"
#include <directxmath.h>
#include <exception>
#include <sstream>

using namespace DirectX;

class DirectX11ConstantBuffer : public IConstantBuffer {
public:
  DirectX11ConstantBuffer(int sizeInBytes);
  ~DirectX11ConstantBuffer();

  char* const getData() const override { return buffer; }
  int getSizeInBytes() const override { return sizeInBytes; }

  void clearBuffer() override;

  char* addMatrix(void* toAdd) override;
  char* addFloat2(void* toAdd) override;
  char* addFloat3(void* toAdd) override;
  char* addFloat4(void* toAdd) override;
  char* addLight(void* toAdd) override;
  char* addMaterial(void* toAdd) override;
  char* addFloat(float toAdd) override;
  char* addInt(int toAdd) override;

  template <class T>
  void addData(T& toAdd);
private:
  int sizeInBytes, currentBufferSize;
  char *buffer, *currentPosition;
};

template <class T>
void addData(T& toAdd) {
  if (currentBufferSize + sizeof(T) <= sizeInBytes) {
    T& insertAt = *(T*) currentPosition;
    insertAt = toAdd;
    currentPosition += sizeof(T);
    currentBufferSize += sizeof(T);
  }
  else {
    std::stringstream errorMessage;
    errorMessage << "Attempting to add more bytes than were allocated: allocated size = " << sizeInBytes << ", total bytes to add = " << (currentBufferSize + sizeof(T));
    throw std::exception(errorMessage.str().c_str());
  }
}