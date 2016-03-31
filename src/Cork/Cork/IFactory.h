#pragma once
#include "IComponent.h"
#include "IDataComponent.h"

class IFactory {
public:
  virtual ~IFactory() {}

  virtual IComponent* const getBasicGraphicsComponent(void* data) const = 0;
  virtual IComponent* const getBasicInputComponent(void* data) const = 0;
  virtual IComponent* const getBasicMovementComponent(void* data) const = 0;
  virtual IComponent* const getDirectX11Graphics(void* data) const = 0;

  virtual IDataComponent* const getTransformComponent(void* data) const = 0;
  virtual IDataComponent* const getMeshComponent(void* data) const = 0;
  virtual IDataComponent* const getCameraComponent(void* data) const = 0;
  virtual IDataComponent* const getLightComponent(void* data) const = 0;
  virtual IDataComponent* const getBoundingBoxComponent(void* data) const = 0;
};