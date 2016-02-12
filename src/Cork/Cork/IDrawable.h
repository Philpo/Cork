#pragma once

class IDrawable {
public:
  virtual ~IDrawable() {}

  virtual void draw() const = 0;
};