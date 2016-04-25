#include "LightComponent.h"

LightComponent::LightComponent() {
  light = new Light;
}

LightComponent::~LightComponent() {
  if (light) {
    delete light;
  }
}

void LightComponent::setData(void* data) {
  Light lightData = *(Light*) data;

  light->cbVariableName = lightData.cbVariableName;
  light->ambient = lightData.ambient;
  light->diffuse = lightData.diffuse;
  light->specular = lightData.specular;
  light->direction = lightData.direction;
  light->attenuation = lightData.attenuation;
  light->range = lightData.range;
  light->exponent = lightData.exponent;
  light->enabled = lightData.enabled;
  light->type = lightData.type;
}