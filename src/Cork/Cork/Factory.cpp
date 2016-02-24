#include "Factory.h"

Factory* Factory::instance;

const Factory& Factory::getFactory() {
  if (!instance) {
    instance = new Factory();
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