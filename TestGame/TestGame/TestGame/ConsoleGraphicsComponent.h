#pragma once
#include "IComponent.h"
#include "Vector3.h"
#include <iostream>

class ConsoleGraphicsComponent : public IComponent {
public:
  ConsoleGraphicsComponent();
  ~ConsoleGraphicsComponent() {}

  const std::string& getType() const override { return GRAPHICS_COMPONENT; }
private:
  void receiveMessage(IMessage& message) override;
};