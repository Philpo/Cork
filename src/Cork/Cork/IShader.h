#pragma once
#include <string>

class IShader {
public:
  virtual ~IShader() {}

  virtual void* const getShader() const = 0;
  virtual const std::string& getType() const = 0;

  virtual void setShader(void* const shader) = 0;
  virtual void setType(const std::string& type) = 0;
};