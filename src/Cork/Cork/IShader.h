#pragma once
#include <string>

class IShader {
public:
  virtual ~IShader() {}

  inline virtual void* const getShader() const = 0;
  inline virtual const std::string& getType() const = 0;

  inline virtual void setShader(void* const shader) = 0;
  inline virtual void setType(const std::string& type) = 0;
};