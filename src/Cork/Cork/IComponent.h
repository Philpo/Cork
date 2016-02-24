#pragma once
#include "Utils.h"
#include "IMessageable.h"

class IComponent : public IMessageable {
public:
  virtual ~IComponent() {}

  inline virtual const std::string& getType() const = 0;
};