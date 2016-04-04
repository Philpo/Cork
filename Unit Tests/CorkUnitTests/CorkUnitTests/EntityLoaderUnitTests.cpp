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
        ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(PARTICLE_COMPONENT, std::bind(&Factory::getParticleComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(JUMP_DATA_COMPONENT, std::bind(&Factory::getJumpDataComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(UPDATE_POSITION_COMPONENT, std::bind(&Factory::getUpdatePositionComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(APPLY_FORCE_COMPONENT, std::bind(&Factory::getApplyForceComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(JUMP_COMPONENT, std::bind(&Factory::getJumpComponent, &factory, std::placeholders::_1));
        GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");

        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        REQUIRE((entity->getDataComponent(CAMERA_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(CAMERA_COMPONENT)) == typeid(CameraComponent));
        REQUIRE((entity->getDataComponent(BOUNDING_BOX_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(BOUNDING_BOX_COMPONENT)) == typeid(BoundingBoxComponent));
        REQUIRE((entity->getDataComponent(PARTICLE_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(PARTICLE_COMPONENT)) == typeid(ParticleComponent));
        REQUIRE((entity->getDataComponent(JUMP_DATA_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(JUMP_DATA_COMPONENT)) == typeid(JumpDataComponent));

        REQUIRE((entity->getMessageHandler(INPUT_RECEIVED_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)) == typeid(BasicMovementComponent));
        REQUIRE((entity->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)) == typeid(UpdatePositionComponent));
        REQUIRE((entity->getMessageHandler(APPLY_FORCE_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(APPLY_FORCE_MESSAGE)) == typeid(ApplyForceComponent));
        REQUIRE((entity->getMessageHandler(JUMP_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(JUMP_MESSAGE)) == typeid(JumpComponent));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(2.0f));
        REQUIRE(data.position.getZ() == approx(-10.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(2.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
        REQUIRE(data.scale.getX() == approx(0.0f));
        REQUIRE(data.scale.getY() == approx(0.0f));
        REQUIRE(data.scale.getZ() == approx(0.0f));
        REQUIRE(data.worldRotation.getX() == approx(0.0f));
        REQUIRE(data.worldRotation.getY() == approx(0.0f));
        REQUIRE(data.worldRotation.getZ() == approx(0.0f));
        REQUIRE((data.parent == nullptr));

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

        BoundingBox boxData = *(BoundingBox*) entity->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(2.0f));
        REQUIRE(boxData.centre.getZ() == approx(-10.0f));
        REQUIRE(boxData.height == approx(4.0f));
        REQUIRE(boxData.width == approx(4.0f));
        REQUIRE(boxData.depth == approx(4.0f));

        Particle particleData = *(Particle*) entity->getDataComponent(PARTICLE_COMPONENT)->getData();
        REQUIRE(particleData.totalForce.getX() == approx(0.0f));
        REQUIRE(particleData.totalForce.getY() == approx(0.0f));
        REQUIRE(particleData.totalForce.getZ() == approx(0.0f));
        REQUIRE(particleData.acceleration.getX() == approx(0.0f));
        REQUIRE(particleData.acceleration.getY() == approx(0.0f));
        REQUIRE(particleData.acceleration.getZ() == approx(0.0f));
        REQUIRE(particleData.velocity.getX() == approx(0.0f));
        REQUIRE(particleData.velocity.getY() == approx(0.0f));
        REQUIRE(particleData.velocity.getZ() == approx(0.0f));
        REQUIRE(particleData.displacement.getX() == approx(0.0f));
        REQUIRE(particleData.displacement.getY() == approx(0.0f));
        REQUIRE(particleData.displacement.getZ() == approx(0.0f));
        REQUIRE(particleData.mass == approx(1.0f));
        REQUIRE(particleData.maxSpeed == approx(100.0f));
        REQUIRE(particleData.gravityEnabled);

        JumpData jumpData = *(JumpData*) entity->getDataComponent(JUMP_DATA_COMPONENT)->getData();
        REQUIRE(jumpData.maxJumpTime == approx(3.0f));
        REQUIRE(jumpData.jumpForce == approx(2.0f));
        REQUIRE(jumpData.jumpControlPower == approx(2.0f));
        REQUIRE(jumpData.jumpTime == approx(0.0f));
        REQUIRE(!jumpData.jumping);
        REQUIRE(!jumpData.falling);

        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }
    }
    
    TEST_CASE("test load entities") {
      SECTION("test load lights") {
        ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(LIGHT_COMPONENT, std::bind(&Factory::getLightComponent, &factory, std::placeholders::_1));
        EntityLoader::loadEntities("..\\CorkUnitTests\\lights.xml", entities);
        GameObject* entity = entities[0];

        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        REQUIRE((entity->getDataComponent(LIGHT_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(LIGHT_COMPONENT)) == typeid(LightComponent));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(5.0f));
        REQUIRE(data.position.getZ() == approx(-10.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(5.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
        REQUIRE(data.scale.getX() == approx(0.0f));
        REQUIRE(data.scale.getY() == approx(0.0f));
        REQUIRE(data.scale.getZ() == approx(0.0f));
        REQUIRE(data.worldRotation.getX() == approx(0.0f));
        REQUIRE(data.worldRotation.getY() == approx(0.0f));
        REQUIRE(data.worldRotation.getZ() == approx(0.0f));
        REQUIRE((data.parent == nullptr));

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
        ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, &factory, std::placeholders::_1));
        ServiceLocator::addDataComponentFunction(PARTICLE_COMPONENT, std::bind(&Factory::getParticleComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(UPDATE_POSITION_COMPONENT, std::bind(&Factory::getUpdatePositionComponent, &factory, std::placeholders::_1));
        ServiceLocator::addMessageHandlerFunction(APPLY_FORCE_COMPONENT, std::bind(&Factory::getApplyForceComponent, &factory, std::placeholders::_1));
        EntityLoader::loadEntities("..\\CorkUnitTests\\game_objects.xml", entities);
        
        GameObject* entity = entities[0];
        REQUIRE((entity != nullptr));
        REQUIRE((entity->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        REQUIRE((entity->getDataComponent(BOUNDING_BOX_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity->getDataComponent(BOUNDING_BOX_COMPONENT)) == typeid(BoundingBoxComponent));
        REQUIRE((entity->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)) == typeid(UpdatePositionComponent));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(0.0f));
        REQUIRE(data.position.getZ() == approx(0.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(0.0f));
        REQUIRE(data.previousPosition.getZ() == approx(0.0f));
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

        BoundingBox boxData = *(BoundingBox*) entity->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(0.0f));
        REQUIRE(boxData.centre.getZ() == approx(0.0f));
        REQUIRE(boxData.height == approx(4.0f));
        REQUIRE(boxData.width == approx(4.0f));
        REQUIRE(boxData.depth == approx(4.0f));


        GameObject* entity1 = entities[1];
        REQUIRE((entity1 != nullptr));
        REQUIRE((entity1->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity1->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        REQUIRE((entity1->getDataComponent(BOUNDING_BOX_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity1->getDataComponent(BOUNDING_BOX_COMPONENT)) == typeid(BoundingBoxComponent));
        REQUIRE((entity1->getDataComponent(PARTICLE_COMPONENT) != nullptr));
        REQUIRE(typeid(*entity1->getDataComponent(PARTICLE_COMPONENT)) == typeid(ParticleComponent));
        REQUIRE((entity1->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity1->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)) == typeid(UpdatePositionComponent));
        REQUIRE((entity1->getMessageHandler(APPLY_FORCE_MESSAGE) != nullptr));
        REQUIRE(typeid(*entity1->getMessageHandler(APPLY_FORCE_MESSAGE)) == typeid(ApplyForceComponent));

        data = *(Transform*) entity1->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(5.0f));
        REQUIRE(data.position.getZ() == approx(0.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(5.0f));
        REQUIRE(data.previousPosition.getZ() == approx(0.0f));
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

        boxData = *(BoundingBox*) entity1->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(5.0f));
        REQUIRE(boxData.centre.getZ() == approx(0.0f));
        REQUIRE(boxData.height == approx(1.0f));
        REQUIRE(boxData.width == approx(1.0f));
        REQUIRE(boxData.depth == approx(1.0f));

        Particle particleData = *(Particle*) entity1->getDataComponent(PARTICLE_COMPONENT)->getData();
        REQUIRE(particleData.totalForce.getX() == approx(0.0f));
        REQUIRE(particleData.totalForce.getY() == approx(0.0f));
        REQUIRE(particleData.totalForce.getZ() == approx(0.0f));
        REQUIRE(particleData.acceleration.getX() == approx(0.0f));
        REQUIRE(particleData.acceleration.getY() == approx(0.0f));
        REQUIRE(particleData.acceleration.getZ() == approx(0.0f));
        REQUIRE(particleData.velocity.getX() == approx(0.0f));
        REQUIRE(particleData.velocity.getY() == approx(0.0f));
        REQUIRE(particleData.velocity.getZ() == approx(0.0f));
        REQUIRE(particleData.displacement.getX() == approx(0.0f));
        REQUIRE(particleData.displacement.getY() == approx(0.0f));
        REQUIRE(particleData.displacement.getZ() == approx(0.0f));
        REQUIRE(particleData.mass == approx(1.0f));
        REQUIRE(particleData.maxSpeed == approx(100.0f));
        REQUIRE(particleData.gravityEnabled);

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