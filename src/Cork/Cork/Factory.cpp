#include "Factory.h"

std::unique_ptr<Factory> Factory::instance;

const Factory& Factory::getFactory() {
  if (!instance) {
    instance.reset(new Factory());
  }
  return *instance;
}

IComponent* const Factory::getBasicGraphicsComponent() const {
  return new ConsoleGraphicsComponent();
}

IComponent* const Factory::getBasicInputComponent() const {
  return new TestInputComponent();
}

IComponent* const Factory::getBasicMovementComponent() const {
  return new BasicMovementComponent();
}

IComponent* const Factory::getDirectX11Graphics() const {
  try {
    return &DirectX11Graphics::getGraphics();
  }
  catch (exception& e) {
    throw;
  }
}