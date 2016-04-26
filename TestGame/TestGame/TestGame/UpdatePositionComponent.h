#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TestGameComponents.h"

class UpdatePositionComponent : public IComponent {
public:
  UpdatePositionComponent() : target(nullptr) {}
  ~UpdatePositionComponent() {}

  const string& getType() const override { return UPDATE_POSITION_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<string> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};