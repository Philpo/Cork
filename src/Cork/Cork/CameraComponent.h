#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct Camera {
  Vector3 position, look, right, up;
};

class CameraComponent : public IDataComponent {
public:
  CameraComponent();
  ~CameraComponent();

  void* getData() override { return camera; }
  void setData(void* data) override;
private:
  Camera* camera;
};