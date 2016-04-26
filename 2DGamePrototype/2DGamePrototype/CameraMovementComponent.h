#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GameComponents.h"
#include <directxmath.h>

using namespace DirectX;

class CameraMovementComponent : public IComponent {
public:
  CameraMovementComponent() : target(nullptr) {}
  ~CameraMovementComponent() {}

  const string& getType() const override { return CAMERA_MOVE_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setTarget(GameObject* const target) { this->target = target; }
private:
  GameObject* target;
  static const vector<string> SUPPORTED_MESSAGES;

  void receiveMessage(IMessage& message) override;
};

