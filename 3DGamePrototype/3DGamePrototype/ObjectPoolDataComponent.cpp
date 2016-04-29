#include "ObjectPoolDataComponent.h"

ObjectPoolDataComponent::~ObjectPoolDataComponent() {
  if (data) {
    if (data->pool) delete data->pool;
    delete data;
  }
}

void ObjectPoolDataComponent::setData(void* data) {
  PoolData toSet = *(PoolData*) data;

  this->data->masterUUId = toSet.masterUUId;
  this->data->pool = toSet.pool;
}