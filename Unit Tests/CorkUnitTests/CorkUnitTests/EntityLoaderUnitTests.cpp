#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace entityloader {
    Factory factory;
    vector<GameObject* const> entities;

    TEST_CASE("test load entity") {
      SECTION("test load camera") {
        ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, &factory, std::placeholders::_1));
        GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");
        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(CAMERA_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(CAMERA_COMPONENT)) == typeid(CameraComponent));
        REQUIRE((entity->getMessageHandler(INPUT_RECEIVED_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)) == typeid(BasicMovementComponent));
        Camera cameraData = *(Camera*) entity->getDataComponent(CAMERA_COMPONENT)->getData();
        REQUIRE(cameraData.look.getX() == approx(0.0f));
        REQUIRE(cameraData.look.getY() == approx(0.0f));
        REQUIRE(cameraData.look.getZ() == approx(1.0f));
        REQUIRE(cameraData.right.getX() == approx(1.0f));
        REQUIRE(cameraData.right.getY() == approx(0.0f));
        REQUIRE(cameraData.right.getZ() == approx(0.0f));
        REQUIRE(cameraData.up.getX() == approx(0.0f));
        REQUIRE(cameraData.up.getY() == approx(1.0f));
        REQUIRE(cameraData.up.getZ() == approx(0.0f));
        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }
    }
    
    TEST_CASE("test load entities") {
      SECTION("test load lights") {
        ServiceLocator::addDataComponentFunction(LIGHT_COMPONENT, std::bind(&Factory::getLightComponent, &factory, std::placeholders::_1));
        EntityLoader::loadEntities("..\\CorkUnitTests\\lights.xml", entities);
        GameObject* entity = entities[0];
        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(LIGHT_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(LIGHT_COMPONENT)) == typeid(LightComponent));
        Light lightData = *(Light*) entity->getDataComponent(LIGHT_COMPONENT)->getData();
        REQUIRE(lightData.range == approx(1000.0f));
        REQUIRE(lightData.type == POINT_LIGHT);
        REQUIRE(lightData.ambient.getX() == approx(0.2f));
        REQUIRE(lightData.ambient.getY() == approx(0.2f));
        REQUIRE(lightData.ambient.getZ() == approx(0.2f));
        REQUIRE(lightData.diffuse.getX() == approx(1.0f));
        REQUIRE(lightData.diffuse.getY() == approx(1.0f));
        REQUIRE(lightData.diffuse.getZ() == approx(1.0f));
        REQUIRE(lightData.specular.getX() == approx(0.5f));
        REQUIRE(lightData.specular.getY() == approx(0.5f));
        REQUIRE(lightData.specular.getZ() == approx(0.5f));
        REQUIRE(lightData.attenuation.getX() == approx(0.0f));
        REQUIRE(lightData.attenuation.getY() == approx(0.1f));
        REQUIRE(lightData.attenuation.getZ() == approx(0.0f));
        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }

      SECTION("test load objects") {
        entities.clear();
        ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, &factory, std::placeholders::_1));
        EntityLoader::loadEntities("..\\CorkUnitTests\\game_objects.xml", entities);
        
        GameObject* entity = entities[0];
        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(0.0f));
        REQUIRE(data.position.getZ() == approx(0.0f));
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
        REQUIRE(data.scale.getX() == approx(2.0f));
        REQUIRE(data.scale.getY() == approx(2.0f));
        REQUIRE(data.scale.getZ() == approx(2.0f));
        REQUIRE(data.worldRotation.getX() == approx(0.0f));
        REQUIRE(data.worldRotation.getY() == approx(0.0f));
        REQUIRE(data.worldRotation.getZ() == approx(0.0f));
        REQUIRE((data.parent == nullptr));

        GameObject* entity1 = entities[1];
        REQUIRE((entity1 != nullptr));
        REQUIRE((entity1->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity1->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        data = *(Transform*) entity1->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(5.0f));
        REQUIRE(data.position.getZ() == approx(0.0f));
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
        REQUIRE(data.scale.getX() == approx(0.5f));
        REQUIRE(data.scale.getY() == approx(0.5f));
        REQUIRE(data.scale.getZ() == approx(0.5f));
        REQUIRE(data.worldRotation.getX() == approx(0.0f));
        REQUIRE(data.worldRotation.getY() == approx(0.0f));
        REQUIRE(data.worldRotation.getZ() == approx(0.0f));
        REQUIRE((data.parent == entity->getDataComponent(TRANSFORM_COMPONENT)->getData()));

        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }
    }

    TEST_CASE("test getEntity") {
      SECTION("test with loaded entity") {
        EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");
        GameObject* entity = EntityLoader::getEntity(1);
        REQUIRE((entity != nullptr));
        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }

      SECTION("test with unloaded entity") {
        GameObject* entity = EntityLoader::getEntity(2);
        REQUIRE((entity == nullptr));
      }
    }
  }
}