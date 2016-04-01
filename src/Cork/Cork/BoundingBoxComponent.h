#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct BoundingBox {
  BoundingBox() : height(0.0f), width(0.0f), depth(0.0f) {}
  Vector3 centre;
  float height, width, depth;
};

class BoundingBoxComponent : public IDataComponent {
public:
  BoundingBoxComponent();
  ~BoundingBoxComponent();

  void* getData() override { return boundingBox; }
  void setData(void* data) override;
private:
  BoundingBox* boundingBox;
};