#pragma once
#include "IComponent.h"
#include "GameObject.h"

class BasicMovementComponent : public IComponent {
public:
  BasicMovementComponent(GameObject& target) : target(target) {}
  ~BasicMovementComponent() {}

  const string& getType() const override { return INPUT_COMPONENT; }
private:
  GameObject& target;
  void receiveMessage(IMessage& message) override;
};