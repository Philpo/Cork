#pragma once
#include "IComponent.h"
#include "ObjectPoolDataComponent.h"
#include "BulletDataComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "BoundingBoxComponent.h"
#include "CameraComponent.h"
#include "GameComponents.h"

class BulletComponent : public IComponent {
public:
  BulletComponent() {}
  ~BulletComponent() {}

  const string& getType() const override { return BULLET_COMPONENT; }
  const vector<string>& getSupportedMessages() const override { return SUPPORTED_MESSAGES; }

  void setEntity(GameObject* const entity) { this->entity = entity; }
private:
  void receiveMessage(IMessage& message) override;

  GameObject* entity;
  static const vector<string> SUPPORTED_MESSAGES;
};