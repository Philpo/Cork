#pragma once
#include "IFactory.h"
#include "TestInputComponent.h"
#include "InputMessenger.h"
#include "DirectX11Graphics.h"
#include "ApplyForceComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "BoundingBoxComponent.h"
#include "ParticleComponent.h"
#include "ResourceManager.h"
#include "EntityLoader.h"
#include "RapidXML\rapidxml.hpp"

using namespace rapidxml;

class Factory : public IFactory {
public:
  Factory() : IFactory() {}
  ~Factory() {}

  virtual IComponent* const getBasicInputComponent(void* data) const override;
  virtual IComponent* const getInputMessenger(void* data) const override;
  virtual IComponent* const getDirectX11Graphics(void* data) const override; 
  virtual IComponent* const getApplyForceComponent(void* data) const override;

  virtual IDataComponent* const getTransformComponent(void* data) const override;
  virtual IDataComponent* const getMeshComponent(void* data) const override;
  virtual IDataComponent* const getCameraComponent(void* data) const override;
  virtual IDataComponent* const getBoundingBoxComponent(void* data) const override;
  virtual IDataComponent* const getParticleComponent(void* data) const override;
};