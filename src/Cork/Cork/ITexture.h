#pragma once

class ITexture {
public:
  virtual ~ITexture() {}

  virtual int getId() const = 0;
  virtual void* getTexture() const = 0;
};