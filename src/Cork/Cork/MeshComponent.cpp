#include "MeshComponent.h"

void MeshComponent::setData(void* data) {
  meshId = *(int*) data;
}