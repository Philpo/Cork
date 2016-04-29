#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct BulletData {
  BulletData() : speed(0.0f) {}

  Vector3 direction;
  float speed;
};

class BulletDataComponent : public IDataComponent {
public:
  BulletDataComponent();
  ~BulletDataComponent();

  void* getData() override { return data; }
  void setData(void* data) override;
private:
  BulletData* data;
};