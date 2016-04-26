#pragma once
#include "Factory.h"
#include "BasicMovementComponent.h"
#include "CameraMovementComponent.h"
#include "UpdatePositionComponent.h"
#include "JumpComponent.h"
#include "LightComponent.h"
#include "JumpDataComponent.h"

class TestGameFactory : public Factory {
public:
  TestGameFactory() {}
  ~TestGameFactory() {}

  IComponent* const getBasicMovementComponent(void* data) const;
  IComponent* const getCameraMoveComponent(void* data) const;
  IComponent* const getUpdatePositionComponent(void* data) const;
  IComponent* const getJumpComponent(void* data) const;

  IDataComponent* const getLightComponent(void* data) const;
  IDataComponent* const getJumpDataComponent(void* data) const;
};