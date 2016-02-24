#pragma once
#include "IComponent.h"
#include "GameObject.h"

class BasicMovementComponent : public IComponent {
public:
  BasicMovementComponent() : target(nullptr) {}
  ~BasicMovementComponent() {}

  const string& getType() const override { return BASIC_MOVE_COMPONENT; }

  inline void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  void receiveMessage(IMessage& message) override;
};