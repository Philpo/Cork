#pragma once
#include "IComponent.h"
#include "JumpDataComponent.h"
#include "ParticleComponent.h"
#include "GameObject.h"

class JumpComponent : public IComponent {
public:
  JumpComponent() {}
  ~JumpComponent() {}

  const string& getType() const override { return JUMP_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<string> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};