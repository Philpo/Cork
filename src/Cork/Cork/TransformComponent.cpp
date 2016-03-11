#include "TransformComponent.h"

TransformComponent::TransformComponent() {
  transform = new Transform;
}

TransformComponent::~TransformComponent() {
  if (transform) {
    delete transform;
  }
}

void* TransformComponent::getData() {
  return transform;
}

void TransformComponent::setData(void* data) {
  Transform* toSet = (Transform*) data;

  transform->position = toSet->position;
  transform->rotation = toSet->rotation;
  transform->scale = toSet->scale;
}