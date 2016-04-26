#include "TestGameFactory.h"

IComponent* const TestGameFactory::getBasicMovementComponent(void* data) const {
  BasicMovementComponent* m = new BasicMovementComponent();
  m->setTarget((GameObject*) data);
  return m;
}

IComponent* const TestGameFactory::getCameraMoveComponent(void* data) const {
  CameraMovementComponent* m = new CameraMovementComponent();
  m->setTarget((GameObject*) data);
  return m;
}

IComponent* const TestGameFactory::getUpdatePositionComponent(void* data) const {
  UpdatePositionComponent* u = new UpdatePositionComponent;
  u->setTarget((GameObject*) data);
  return u;
}

IComponent* const TestGameFactory::getJumpComponent(void* data) const {
  JumpComponent* jc = new JumpComponent;
  jc->setTarget((GameObject*) data);
  return jc;
}

IDataComponent* const TestGameFactory::getLightComponent(void* data) const {
  LightComponent* light = new LightComponent;
  Light lightData;

  if (data) {
    xml_node<>* lightNode = (xml_node<>*) data;

    try {
      if (lightNode->first_attribute("range")) {
        lightData.range = convertStringToNumber<float>(lightNode->first_attribute("range")->value());
      }

      if (lightNode->first_attribute("exponent")) {
        lightData.exponent = convertStringToNumber<float>(lightNode->first_attribute("exponent")->value());
      }

      lightData.enabled = true;
      lightData.type = convertStringToNumber<int>(lightNode->first_attribute("light_type")->value());

      xml_node<>* component = lightNode->first_node("ambient");
      lightData.ambient.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      lightData.ambient.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      lightData.ambient.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = lightNode->first_node("diffuse");
      lightData.diffuse.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      lightData.diffuse.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      lightData.diffuse.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = lightNode->first_node("specular");
      lightData.specular.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      lightData.specular.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      lightData.specular.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      if (lightNode->first_node("direction")) {
        component = lightNode->first_node("direction");
        lightData.direction.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
        lightData.direction.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
        lightData.direction.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));
      }

      if (lightNode->first_node("attenuation")) {
        component = lightNode->first_node("attenuation");
        lightData.attenuation.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
        lightData.attenuation.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
        lightData.attenuation.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));
      }

      light->setData(&lightData);
    }
    catch (exception&) {
      delete light;
      throw;
    }
  }

  return light;
}

IDataComponent* const TestGameFactory::getJumpDataComponent(void* data) const {
  JumpDataComponent* jump = new JumpDataComponent;
  JumpData jumpData;

  if (data) {
    xml_node<>* jumpNode = (xml_node<>*) data;

    try {
      jumpData.maxJumpTime = convertStringToNumber<float>(jumpNode->first_attribute("max_jump_time")->value());
      jumpData.jumpForce = convertStringToNumber<float>(jumpNode->first_attribute("jump_force")->value());
      jumpData.jumpControlPower = convertStringToNumber<float>(jumpNode->first_attribute("jump_control_power")->value());

      jump->setData(&jumpData);
    }
    catch (exception&) {
      delete jump;
      throw;
    }
  }

  return jump;
}