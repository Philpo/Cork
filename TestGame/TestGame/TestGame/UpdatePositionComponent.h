#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TestGameComponents.h"

class UpdatePositionComponent : public IComponent {
public:
  UpdatePositionComponent() : target(nullptr) {}
  ~UpdatePositionComponent() {}

  size_t getType() const override { return UPDATE_POSITION_COMPONENT; }
  const vector<size_t>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<size_t> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};