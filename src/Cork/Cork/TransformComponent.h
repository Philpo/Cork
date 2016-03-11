#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct Transform {
  Vector3<float> position, rotation, scale;
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