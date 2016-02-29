#pragma once

class IVertex {
public:
  virtual void* getPosition() const = 0;
  virtual void* getNormal() const = 0;
  virtual void* getTangent() const = 0;
  virtual void* getTexCoords() const = 0;
};