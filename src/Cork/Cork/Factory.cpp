#include "Factory.h"

IComponent* const Factory::getBasicInputComponent(void* data) const {
  TestInputComponent* c = new TestInputComponent();
  c->setPlayer((IMessageable*) data);
  return c;
}

IComponent* const Factory::getDirectX11Graphics(void* data) const {
  try {
    return &DirectX11Graphics::getGraphics();
  }
  catch (exception&) {
    throw;
  }
}

IComponent* const Factory::getApplyForceComponent(void* data) const {
  ApplyForceComponent* a = new ApplyForceComponent;
  if (data) {
    GameObject* go = (GameObject*) data;
    if (go->getDataComponent(PARTICLE_COMPONENT)) {
      a->setParticle((Particle*) go->getDataComponent(PARTICLE_COMPONENT)->getData());
    }
  }
  return a;
}

IDataComponent* const Factory::getTransformComponent(void* data) const {
  TransformComponent* transform = new TransformComponent;
  Transform transformData;

  if (data) {
    xml_node<>* transformNode = (xml_node<>*) data;

    try {
      if (transformNode->first_attribute("parent")) {
        int parentUId = convertStringToNumber<int>(transformNode->first_attribute("parent")->value());
        GameObject* parent = EntityLoader::getEntity(parentUId);
        if (parent) {
          transformData.parent = (Transform*) parent->getDataComponent(TRANSFORM_COMPONENT)->getData();
        }
      }

      xml_node<>* component = transformNode->first_node("position");
      transformData.position.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      transformData.position.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      transformData.position.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      transformData.previousPosition = transformData.position;

      component = transformNode->first_node("local_rotation");
      transformData.localRotation.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      transformData.localRotation.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      transformData.localRotation.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = transformNode->first_node("scale");
      transformData.scale.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      transformData.scale.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      transformData.scale.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = transformNode->first_node("world_rotation");
      transformData.worldRotation.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      transformData.worldRotation.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      transformData.worldRotation.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      transform->setData(&transformData);
    }
    catch (exception&) {
      delete transform;
      throw;
    }
  }

  return transform;
}

IDataComponent* const Factory::getMeshComponent(void* data) const {
  MeshComponent* mesh = new MeshComponent;
  int meshId;

  if (data) {
    xml_node<>* meshNode = (xml_node<>*) data;

    try {
      string meshFile = meshNode->first_attribute("mesh_file")->value();
      ResourceManager::loadMesh(meshFile, meshId);

      mesh->setData(&meshId);
    }
    catch (exception&) {
      delete mesh;
      throw;
    }
  }

  return mesh;
}

IDataComponent* const Factory::getCameraComponent(void* data) const {
  CameraComponent* camera = new CameraComponent;
  Camera cameraData;

  if (data) {
    xml_node<>* cameraNode = (xml_node<>*) data;

    try {
      xml_node<>* component = cameraNode->first_node("look");
      cameraData.look.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      cameraData.look.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      cameraData.look.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = cameraNode->first_node("right");
      cameraData.right.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      cameraData.right.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      cameraData.right.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      component = cameraNode->first_node("up");
      cameraData.up.setX(convertStringToNumber<float>(component->first_attribute("x")->value()));
      cameraData.up.setY(convertStringToNumber<float>(component->first_attribute("y")->value()));
      cameraData.up.setZ(convertStringToNumber<float>(component->first_attribute("z")->value()));

      camera->setData(&cameraData);
    }
    catch (exception&) {
      delete camera;
      throw;
    }
  }

  return camera;
}

IDataComponent* const Factory::getBoundingBoxComponent(void* data) const {
  BoundingBoxComponent* boundingBox = new BoundingBoxComponent;
  BoundingBox boxData;

  if (data) {
    xml_node<>* boxNode = (xml_node<>*) data;

    try {
      boxData.height = convertStringToNumber<float>(boxNode->first_attribute("height")->value());
      boxData.width = convertStringToNumber<float>(boxNode->first_attribute("width")->value());
      boxData.depth = convertStringToNumber<float>(boxNode->first_attribute("depth")->value());

      xml_node<>* centreNode = boxNode->first_node("centre");
      boxData.centre.setX(convertStringToNumber<float>(centreNode->first_attribute("x")->value()));
      boxData.centre.setY(convertStringToNumber<float>(centreNode->first_attribute("y")->value()));
      boxData.centre.setZ(convertStringToNumber<float>(centreNode->first_attribute("z")->value()));

      boundingBox->setData(&boxData);
    }
    catch (exception&) {
      delete boundingBox;
      throw;
    }
  }

  return boundingBox;
}

IDataComponent* const Factory::getParticleComponent(void* data) const {
  ParticleComponent* particle = new ParticleComponent;
  Particle particleData;

  if (data) {
    xml_node<>* particleNode = (xml_node<>*) data;

    try {
      particleData.mass = convertStringToNumber<float>(particleNode->first_attribute("mass")->value());
      particleData.maxSpeed = convertStringToNumber<float>(particleNode->first_attribute("max_speed")->value());

      particle->setData(&particleData);
    }
    catch (exception&) {
      delete particle;
      throw;
    }
  }

  return particle;
}