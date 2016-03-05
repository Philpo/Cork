#pragma once

class IConstantBuffer {
public:
  virtual ~IConstantBuffer() {}

  virtual inline char* const getData() const = 0;
  virtual inline int getSizeInBytes() const = 0;

  virtual void clearBuffer() = 0;

  virtual char* addMatrix(void* toAdd) = 0;
  virtual char* addFloat2(void* toAdd) = 0;
  virtual char* addFloat3(void* toAdd) = 0;
  virtual char* addFloat4(void* toAdd) = 0;
  virtual char* addLight(void* toAdd) = 0;
  virtual char* addMaterial(void* toAdd) = 0;
  virtual char* addFloat(float toAdd) = 0;
  virtual char* addInt(int toAdd) = 0;
};