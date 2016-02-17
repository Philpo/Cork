#pragma once
#include "IComponent.h"
#include "Vector3.h"
#include <iostream>

class ConsoleGraphicsComponent : public IComponent {
public:
  ConsoleGraphicsComponent();
  ~ConsoleGraphicsComponent() {}

  ComponentType getType() const override { return GRAPHICS_COMPONENT; }
  void receiveMessage(const IMessage& message) override;
};