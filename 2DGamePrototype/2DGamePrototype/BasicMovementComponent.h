#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameComponents.h"
#include "Message.h"

class BasicMovementComponent : public IComponent {
public:
  BasicMovementComponent() : target(nullptr) {}
  ~BasicMovementComponent() {}

  size_t getType() const override { return BASIC_MOVE_COMPONENT; }
  const vector<size_t>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<size_t> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};