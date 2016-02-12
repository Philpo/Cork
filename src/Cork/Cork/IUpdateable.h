#pragma once

class IUpdateable {
public:
  virtual ~IUpdateable() {}

  virtual void update(double timeSinceLastFrame) = 0;
};