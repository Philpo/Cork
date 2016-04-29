#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameComponents.h"

class BasicMovementComponent : public IComponent {
public:
  BasicMovementComponent() : target(nullptr) {}
  ~BasicMovementComponent() {}

  const string& getType() const override { return BASIC_MOVE_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<string> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};