#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

class UpdatePositionComponent : public IComponent {
public:
  UpdatePositionComponent() : target(nullptr) {}
  ~UpdatePositionComponent() {}

  const string& getType() const override { return UPDATE_POSITION_COMPONENT; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;

  void receiveMessage(IMessage& message) override;
};