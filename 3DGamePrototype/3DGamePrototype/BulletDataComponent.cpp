#include "BulletDataComponent.h"

BulletDataComponent::BulletDataComponent() : data(new BulletData) {}

BulletDataComponent::~BulletDataComponent() {
  delete data;
}

void BulletDataComponent::setData(void* data) {
  BulletData* toSet = (BulletData*) data;
  this->data->direction = toSet->direction;
  this->data->speed = toSet->speed;
}