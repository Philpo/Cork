#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace jump {
    Factory factory;

    TEST_CASE("test jump getSupportedMessages") {
      IComponent* c = new JumpComponent;
      REQUIRE(c->getSupportedMessages().size() == 1);
      REQUIRE(c->getSupportedMessages()[0] == JUMP_MESSAGE);
      delete c;
    }

    TEST_CASE("test jump receiveMessage") {
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
      double time = 16;

      MessageHandler::forwardMessage(Message(JUMP_MESSAGE, &time, entity->getMessageHandler(JUMP_MESSAGE)));

      JumpData data = *(JumpData*) entity->getDataComponent(JUMP_DATA_COMPONENT)->getData();

      REQUIRE(data.jumpTime == approx(0.016f));
      REQUIRE(data.jumping);
      REQUIRE(!data.falling);

      Particle particleData = *(Particle*) entity->getDataComponent(PARTICLE_COMPONENT)->getData();

      REQUIRE(particleData.totalForce.getX() == approx(0.0f));
      REQUIRE(particleData.totalForce.getY() == approx(1.99994f));
      REQUIRE(particleData.totalForce.getZ() == approx(0.0f));

      EntityLoader::cleanup();
      ServiceLocator::cleanup();
    }
  }
}