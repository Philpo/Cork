#pragma once
#include "IFactory.h"
#include "TestInputComponent.h"
#include "BasicMovementComponent.h"
#include "CameraMovementComponent.h"
#include "DirectX11Graphics.h"
#include "UpdatePositionComponent.h"
#include "ApplyForceComponent.h"
#include "JumpComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "BoundingBoxComponent.h"
#include "ParticleComponent.h"
#include "JumpDataComponent.h"
#include "ResourceManager.h"
#include "EntityLoader.h"
#include "RapidXML\rapidxml.hpp"

using namespace rapidxml;

class Factory : public IFactory {
public:
  Factory() : IFactory() {}
  ~Factory() {}

  virtual IComponent* const getBasicInputComponent(void* data) const override;
  virtual IComponent* const getBasicMovementComponent(void* data) const override;
  virtual IComponent* const getCameraMoveComponent(void* data) const override;
  virtual IComponent* const getDirectX11Graphics(void* data) const override; 
  virtual IComponent* const getUpdatePositionComponent(void* data) const override;
  virtual IComponent* const getApplyForceComponent(void* data) const override;
  virtual IComponent* const getJumpComponent(void* data) const override;

  virtual IDataComponent* const getTransformComponent(void* data) const override;
  virtual IDataComponent* const getMeshComponent(void* data) const override;
  virtual IDataComponent* const getCameraComponent(void* data) const override;
  virtual IDataComponent* const getLightComponent(void* data) const override;
  virtual IDataComponent* const getBoundingBoxComponent(void* data) const override;
  virtual IDataComponent* const getParticleComponent(void* data) const override;
  virtual IDataComponent* const getJumpDataComponent(void* data) const override;
};