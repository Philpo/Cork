#pragma once
#include "IComponent.h"
#include "GameObject.h"

class BasicMovementComponent : public IComponent {
public:
  BasicMovementComponent(GameObject& target) : target(target) {}
  ~BasicMovementComponent() {}

  ComponentType getType() const override { return INPUT_COMPONENT; }
  void receiveMessage(const IMessage& message) override;
private:
  GameObject& target;
};