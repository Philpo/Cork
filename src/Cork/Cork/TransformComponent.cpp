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
  transform->localRotation = toSet->localRotation;
  transform->scale = toSet->scale;
  transform->parent = toSet->parent;
}