#pragma once
#include "Utils.h"
#include "IMessageable.h"

class IComponent : public IMessageable {
public:
  virtual ~IComponent() {}

  virtual size_t getType() const = 0;
};