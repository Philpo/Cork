#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace updateposition {
    Factory factory;

    TEST_CASE("test updateposition getSupportedMessages") {
      IComponent* c = new UpdatePositionComponent;
      REQUIRE(c->getSupportedMessages().size() == 1);
      REQUIRE(c->getSupportedMessages()[0] == UPDATE_AFTER_COLLISION_MESSAGE);
      delete c;
    }

    TEST_CASE("test updateposition receiveMessage") {
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
      Vector3 newPos(-10.5f, 0.002f, 100.365f);

      MessageHandler::forwardMessage(Message(UPDATE_AFTER_COLLISION_MESSAGE, &newPos, entity->getMessageHandler(UPDATE_AFTER_COLLISION_MESSAGE)));

      Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
      REQUIRE(data.position.getX() == approx(-10.5f));
      REQUIRE(data.position.getY() == approx(0.002f));
      REQUIRE(data.position.getZ() == approx(100.365f));

      EntityLoader::cleanup();
      ServiceLocator::cleanup();
    }
  }
}