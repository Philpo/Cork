#pragma once
#include "IDataComponent.h"

class MeshComponent : public IDataComponent {
public:
  MeshComponent() : meshId(-1) {}
  ~MeshComponent() {}

  void* getData() override { return &meshId; }
  void setData(void* data) override;
private:
  int meshId;
};