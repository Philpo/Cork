#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace basicmovement {
    Factory factory;

    TEST_CASE("test basicmovement getSupportedMessages") {
      IComponent* c = new BasicMovementComponent;
      REQUIRE(c->getSupportedMessages().size() == 1);
      REQUIRE(c->getSupportedMessages()[0] == INPUT_RECEIVED_MESSAGE);
      delete c;
    }

    TEST_CASE("test basicmovement receiveMessage") {
      ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, &factory, std::placeholders::_1));
      ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, &factory, std::placeholders::_1));
      ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, &factory, std::placeholders::_1));
      ServiceLocator::addMessageHandlerFunction(BASIC_MOVE_COMPONENT, std::bind(&Factory::getBasicMovementComponent, &factory, std::placeholders::_1));
      ServiceLocator::addMessageHandlerFunction(UPDATE_POSITION_COMPONENT, std::bind(&Factory::getUpdatePositionComponent, &factory, std::placeholders::_1));
      GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");

      SECTION("test basicmovement move forward") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &MOVE_FORWARD, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(2.0f));
        REQUIRE(data.position.getZ() == approx(-9.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(2.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
      }

      SECTION("test basicmovement move backward") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &MOVE_BACK, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(0.0f));
        REQUIRE(data.position.getY() == approx(2.0f));
        REQUIRE(data.position.getZ() == approx(-11.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(2.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
      }

      SECTION("test basicmovement strafe left") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &MOVE_LEFT, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(-1.0f));
        REQUIRE(data.position.getY() == approx(2.0f));
        REQUIRE(data.position.getZ() == approx(-10.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(2.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
      }

      SECTION("test basicmovement strafe right") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &MOVE_RIGHT, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.position.getX() == approx(1.0f));
        REQUIRE(data.position.getY() == approx(2.0f));
        REQUIRE(data.position.getZ() == approx(-10.0f));
        REQUIRE(data.previousPosition.getX() == approx(0.0f));
        REQUIRE(data.previousPosition.getY() == approx(2.0f));
        REQUIRE(data.previousPosition.getZ() == approx(-10.0f));
      }

      SECTION("test basicmovement rotate up") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &ROTATE_PITCH_UP, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.localRotation.getX() == approx(-1.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
      }

      SECTION("test basicmovement rotate down") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &ROTATE_PITCH_DOWN, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.localRotation.getX() == approx(1.0f));
        REQUIRE(data.localRotation.getY() == approx(0.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
      }

      SECTION("test basicmovement rotate left") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &ROTATE_YAW_ANTICLOCKWISE, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(-1.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
      }

      SECTION("test basicmovement rotate right") {
        MessageHandler::forwardMessage(Message(INPUT_RECEIVED_MESSAGE, (void*) &ROTATE_YAW_CLOCKWISE, entity->getMessageHandler(INPUT_RECEIVED_MESSAGE)));

        Transform data = *(Transform*) entity->getDataComponent(TRANSFORM_COMPONENT)->getData();
        REQUIRE(data.localRotation.getX() == approx(0.0f));
        REQUIRE(data.localRotation.getY() == approx(1.0f));
        REQUIRE(data.localRotation.getZ() == approx(0.0f));
      }

      EntityLoader::cleanup();
      ServiceLocator::cleanup();
    }
  }
}