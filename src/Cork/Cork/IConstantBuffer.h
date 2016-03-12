#pragma once
#include <string>

using namespace std;

class IConstantBuffer {
public:
  virtual ~IConstantBuffer() {}

  virtual inline char* const getData() const = 0;
  virtual inline int getSizeInBytes() const = 0;

  virtual void clearBuffer() = 0;

  virtual void addMatrix(string variableName, void* toAdd) = 0;
  virtual void addFloat2(string variableName, void* toAdd) = 0;
  virtual void addFloat3(string variableName, void* toAdd) = 0;
  virtual void addFloat4(string variableName, void* toAdd) = 0;
  virtual void addLight(string variableName, void* toAdd) = 0;
  virtual void addMaterial(string variableName, void* toAdd) = 0;
  virtual void addFloat(string variableName, float toAdd) = 0;
  virtual void addInt(string variableName, int toAdd) = 0;

  virtual void updateMatrix(string variableName, void* data) = 0;
  virtual void updateFloat2(string variableName, void* data) = 0;
  virtual void updateFloat3(string variableName, void* data) = 0;
  virtual void updateFloat4(string variableName, void* data) = 0;
  virtual void updateLight(string variableName, void* data) = 0;
  virtual void updateMaterial(string variableName, void* data) = 0;
  virtual void updateFloat(string variableName, float data) = 0;
  virtual void updateInt(string variableName, int data) = 0;
};