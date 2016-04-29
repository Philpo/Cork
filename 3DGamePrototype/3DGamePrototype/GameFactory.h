#pragma once
#include "Factory.h"
#include "BasicMovementComponent.h"
#include "CameraMovementComponent.h"
#include "UpdatePositionComponent.h"
#include "BulletComponent.h"
#include "JumpComponent.h"
#include "LightComponent.h"
#include "JumpDataComponent.h"
#include "BulletDataComponent.h"
#include "ObjectPoolDataComponent.h"
#include "ObjectPool.h"

class GameFactory : public Factory {
public:
  GameFactory() {}
  ~GameFactory() {}

  IComponent* const getBasicMovementComponent(void* data) const;
  IComponent* const getCameraMoveComponent(void* data) const;
  IComponent* const getUpdatePositionComponent(void* data) const;
  IComponent* const getBulletComponent(void* data) const;
  IComponent* const getJumpComponent(void* data) const;

  IDataComponent* const getLightComponent(void* data) const;
  IDataComponent* const getJumpDataComponent(void* data) const;
  IDataComponent* const getBulletDataComponent(void* data) const;
  IDataComponent* const getObjectPoolDataComponent(void* data) const;
};