#pragma once
#include "IDataComponent.h"
#include "ObjectPool.h"

struct PoolData {
  ObjectPool* pool = nullptr;
  int masterUUId = 0;
};

class ObjectPoolDataComponent : public IDataComponent {
public:
  ObjectPoolDataComponent() : data(new PoolData) {}
  ~ObjectPoolDataComponent();

  void* getData() override { return data; }
  void setData(void* data) override;
private:
  PoolData* data;
};