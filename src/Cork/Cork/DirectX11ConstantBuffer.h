#pragma once
#include "IConstantBuffer.h"
#include "DirectX11TypeDefs.h"
#include <directxmath.h>
#include <exception>
#include <sstream>
#include <map>

using namespace DirectX;

class DirectX11ConstantBuffer : public IConstantBuffer {
public:
  DirectX11ConstantBuffer(int sizeInBytes);
  ~DirectX11ConstantBuffer();

  char* const getData() const override { return buffer; }
  int getSizeInBytes() const override { return sizeInBytes; }

  void clearBuffer() override;

  void addMatrix(string variableName, void* toAdd) override;
  void addFloat2(string variableName, void* toAdd) override;
  void addFloat3(string variableName, void* toAdd) override;
  void addFloat4(string variableName, void* toAdd) override;
  void addLight(string variableName, void* toAdd) override;
  void addMaterial(string variableName, void* toAdd) override;
  void addFloat(string variableName, float toAdd) override;
  void addInt(string variableName, int toAdd) override;

  void updateMatrix(string variableName, void* data) override;
  void updateFloat2(string variableName, void* data) override;
  void updateFloat3(string variableName, void* data) override;
  void updateFloat4(string variableName, void* data) override;
  void updateLight(string variableName, void* data) override;
  void updateMaterial(string variableName, void* data) override;
  void updateFloat(string variableName, float data) override;
  void updateInt(string variableName, int data) override;

  template <class T>
  void addData(T& toAdd);
private:
  int sizeInBytes, currentBufferSize;
  char *buffer, *currentPosition;
  map<string, char*> variablePositions;
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