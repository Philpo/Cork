#pragma once
#include <memory>
#include "IFactory.h"
#include "ConsoleGraphicsComponent.h"
#include "TestInputComponent.h"
#include "BasicMovementComponent.h"
#include "DirectX11Graphics.h"

class Factory : public IFactory {
public:
  ~Factory() {}

  static const Factory& getFactory();

  IComponent* const getBasicGraphicsComponent() const override;
  IComponent* const getBasicInputComponent() const override;
  IComponent* const getBasicMovementComponent() const override;
  IComponent* const getDirectX11Graphics() const override;
protected:
  Factory() : IFactory() {}
private:
  static std::unique_ptr<Factory> instance;
};