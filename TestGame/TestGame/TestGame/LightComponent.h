#pragma once
#include "IDataComponent.h"
#include "Vector3.h"
#include <string>

enum LightType { DIRECTIONAL_LIGHT = 0, POINT_LIGHT = 1, SPOT_LIGHT = 2 };

struct Light {
  Light() : range(0.0f), exponent(0.0f), enabled(true), cbVariableName("") {}
  std::string cbVariableName;
  Vector3 ambient, diffuse, specular, direction, attenuation;
  float range, exponent;
  int enabled, type;
};

class LightComponent : public IDataComponent {
public:
  LightComponent();
  ~LightComponent();

  void* getData() override { return light; }
  void setData(void* data) override;
private:
  Light* light;
};