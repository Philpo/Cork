#pragma once
#include <string>

class ITexture {
public:
  virtual ~ITexture() {}

  virtual int getId() const = 0;
  virtual const std::string& getType() const = 0;
  virtual void* const getTexture() const = 0;
};