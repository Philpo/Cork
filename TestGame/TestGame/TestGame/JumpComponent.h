#pragma once
#include "IComponent.h"
#include "JumpDataComponent.h"
#include "ParticleComponent.h"
#include "GameObject.h"
#include "TestGameComponents.h"

class JumpComponent : public IComponent {
public:
  JumpComponent() {}
  ~JumpComponent() {}

  size_t getType() const override { return JUMP_COMPONENT; }
  const vector<size_t>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<size_t> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};