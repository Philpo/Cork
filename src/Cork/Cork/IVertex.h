#pragma once

class IVertex {
public:
  virtual ~IVertex() {}

  virtual char* const getData() const = 0;
  virtual int getSizeInBytes() const = 0;

  virtual void addFloat2(void* toAdd) = 0;
  virtual void addFloat3(void* toAdd) = 0;
  virtual void addFloat4(void* toAdd) = 0;
};