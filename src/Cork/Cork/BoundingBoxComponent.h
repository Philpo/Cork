#pragma once
#include "IDataComponent.h"
#include "Vector3.h"

struct BoundingBox {
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