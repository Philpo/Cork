#include "BoundingBoxComponent.h"

BoundingBoxComponent::BoundingBoxComponent() {
  boundingBox = new BoundingBox;
}

BoundingBoxComponent::~BoundingBoxComponent() {
  delete boundingBox;
}

void BoundingBoxComponent::setData(void* data) {
  BoundingBox box = *(BoundingBox*) data;

  boundingBox->centre = box.centre;
  boundingBox->height = box.height;
  boundingBox->width = box.width;
  boundingBox->depth = box.depth;
}