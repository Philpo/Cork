#pragma once
#include "IFactory.h"
#include "ConsoleGraphicsComponent.h"
#include "TestInputComponent.h"
#include "BasicMovementComponent.h"

class Factory : public IFactory {
public:
  static const Factory& getFactory();
  static const void deleteFactory() { if (instance) { delete instance; } }

  IComponent* const getBasicGraphicsComponent() const override;
  IComponent* const getBasicInputComponent() const override;
  IComponent* const getBasicMovementComponent() const override;
protected:
  Factory() : IFactory() {}
  ~Factory() {}
private:
  static Factory* instance;
};