#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct Transform {
  Transform() : parent(nullptr) {}
  Vector3 position, previousPosition, localRotation, scale, worldRotation;
  Transform* parent;
};

class TransformComponent : public IDataComponent {
public:
  TransformComponent();
  ~TransformComponent();

  void* getData() override;
  void setData(void* data) override;
private:
  Transform* transform;
};