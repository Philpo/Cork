#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "ObjectPool.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace objectpool {
    Factory factory;

    TEST_CASE("test objectpool constructor") {
      ObjectPool pool(10);
      REQUIRE(pool.getSize() == 10);
      REQUIRE(pool.getAvailableSpace() == 10);
      REQUIRE(pool.getUsedSpace() == 0);
    }

    TEST_CASE("test objectpool createObject") {
      SECTION("test empty pool") {
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
        ObjectPool pool(10);
        GameObject* created = pool.createObject(1);

        REQUIRE(pool.getAvailableSpace() == 9);
        REQUIRE(pool.getUsedSpace() == 1);

        REQUIRE((created != nullptr));
        REQUIRE((created->getDataComponent(TRANSFORM_COMPONENT) != nullptr));
        REQUIRE(typeid(*created->getDataComponent(TRANSFORM_COMPONENT)) == typeid(TransformComponent));
        REQUIRE((created->getDataComponent(CAMERA_COMPONENT) != nullptr));
        REQUIRE(typeid(*created->getDataComponent(CAMERA_COMPONENT)) == typeid(CameraComponent));
        REQUIRE((created->getDataComponent(BOUNDING_BOX_COMPONENT) != nullptr));
        REQUIRE(typeid(*created->getDataComponent(BOUNDING_BOX_COMPONENT)) == typeid(BoundingBoxComponent));
        REQUIRE((created->getDataComponent(PARTICLE_COMPONENT) != nullptr));
        REQUIRE(typeid(*created->getDataComponent(PARTICLE_COMPONENT)) == typeid(ParticleComponent));
        REQUIRE((created->getDataComponent(JUMP_DATA_COMPONENT) != nullptr));
        REQUIRE(typeid(*created->getDataComponent(JUMP_DATA_COMPONENT)) == typeid(JumpDataComponent));

        REQUIRE((created->getMessageHandler(INPUT_RECEIVED_MESSAGE) != nullptr));
        REQUIRE(typeid(*created->getMessageHandler(INPUT_RECEIVED_MESSAGE)) == typeid(BasicMovementComponent));
        REQUIRE((created->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE) != nullptr));
        REQUIRE(typeid(*created->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)) == typeid(UpdatePositionComponent));
        REQUIRE((created->getMessageHandler(APPLY_FORCE_MESSAGE) != nullptr));
        REQUIRE(typeid(*created->getMessageHandler(APPLY_FORCE_MESSAGE)) == typeid(ApplyForceComponent));
        REQUIRE((created->getMessageHandler(JUMP_MESSAGE) != nullptr));
        REQUIRE(typeid(*created->getMessageHandler(JUMP_MESSAGE)) == typeid(JumpComponent));

        Transform data = *(Transform*) created->getDataComponent(TRANSFORM_COMPONENT)->getData();
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

        Camera cameraData = *(Camera*) created->getDataComponent(CAMERA_COMPONENT)->getData();
        REQUIRE(cameraData.look.getX() == approx(0.0f));
        REQUIRE(cameraData.look.getY() == approx(0.0f));
        REQUIRE(cameraData.look.getZ() == approx(1.0f));
        REQUIRE(cameraData.right.getX() == approx(1.0f));
        REQUIRE(cameraData.right.getY() == approx(0.0f));
        REQUIRE(cameraData.right.getZ() == approx(0.0f));
        REQUIRE(cameraData.up.getX() == approx(0.0f));
        REQUIRE(cameraData.up.getY() == approx(1.0f));
        REQUIRE(cameraData.up.getZ() == approx(0.0f));

        BoundingBox boxData = *(BoundingBox*) created->getDataComponent(BOUNDING_BOX_COMPONENT)->getData();
        REQUIRE(boxData.centre.getX() == approx(0.0f));
        REQUIRE(boxData.centre.getY() == approx(2.0f));
        REQUIRE(boxData.centre.getZ() == approx(-10.0f));
        REQUIRE(boxData.height == approx(4.0f));
        REQUIRE(boxData.width == approx(4.0f));
        REQUIRE(boxData.depth == approx(4.0f));

        Particle particleData = *(Particle*) created->getDataComponent(PARTICLE_COMPONENT)->getData();
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

        JumpData jumpData = *(JumpData*) created->getDataComponent(JUMP_DATA_COMPONENT)->getData();
        REQUIRE(jumpData.maxJumpTime == approx(3.0f));
        REQUIRE(jumpData.jumpForce == approx(2.0f));
        REQUIRE(jumpData.jumpControlPower == approx(2.0f));
        REQUIRE(jumpData.jumpTime == approx(0.0f));
        REQUIRE(!jumpData.jumping);
        REQUIRE(!jumpData.falling);

        EntityLoader::cleanup();
        ServiceLocator::cleanup();
      }

      SECTION("test full pool") {
        GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");
        ObjectPool pool(1);
        GameObject* created = pool.createObject(1);
        GameObject* created2 = pool.createObject(1);

        REQUIRE((created2 == nullptr));
        REQUIRE(pool.getAvailableSpace() == 0);
        REQUIRE(pool.getUsedSpace() == 1);
      }
    }

    TEST_CASE("test objectpool removeObject") {
      SECTION("test objectpool with stored object") {
        GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");
        ObjectPool pool(10);
        GameObject* created = pool.createObject(1);
        pool.removeObject(created);

        REQUIRE(pool.getAvailableSpace() == 10);
        REQUIRE(pool.getUsedSpace() == 0);
      }

      SECTION("test objectpool with non-stored object") {
        ObjectPool pool(10);
        GameObject* go = new GameObject;
        pool.removeObject(go);

        REQUIRE(pool.getAvailableSpace() == 10);
        REQUIRE(pool.getUsedSpace() == 0);
      }
    }
  }
}