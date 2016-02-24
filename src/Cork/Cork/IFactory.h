#pragma once
#include "IComponent.h"

class IFactory {
public:
  virtual ~IFactory() {}

  inline virtual IComponent* const getBasicGraphicsComponent() const = 0;
  inline virtual IComponent* const getBasicInputComponent() const = 0;
  inline virtual IComponent* const getBasicMovementComponent() const = 0;
};