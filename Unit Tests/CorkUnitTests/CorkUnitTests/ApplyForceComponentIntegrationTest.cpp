#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"
#include "EntityLoader.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace applyforce {
    Factory factory;

    TEST_CASE("test applyforce getSupportedMessages") {
      IComponent* c = new ApplyForceComponent;
      REQUIRE(c->getSupportedMessages().size() == 1);
      REQUIRE(c->getSupportedMessages()[0] == APPLY_FORCE_MESSAGE);
      delete c;
    }

    TEST_CASE("test applyforce receiveMessage") {
      ServiceLocator::addDataComponentFunction(TRANSFORM_COMPONENT, std::bind(&Factory::getTransformComponent, &factory, std::placeholders::_1));
      ServiceLocator::addDataComponentFunction(CAMERA_COMPONENT, std::bind(&Factory::getCameraComponent, &factory, std::placeholders::_1));
      ServiceLocator::addDataComponentFunction(BOUNDING_BOX_COMPONENT, std::bind(&Factory::getBoundingBoxComponent, &factory, std::placeholders::_1));
      ServiceLocator::addDataComponentFunction(PARTICLE_COMPONENT, std::bind(&Factory::getParticleComponent, &factory, std::placeholders::_1));
      ServiceLocator::addMessageHandlerFunction(APPLY_FORCE_COMPONENT, std::bind(&Factory::getApplyForceComponent, &factory, std::placeholders::_1));
      GameObject* entity = EntityLoader::loadEntity("..\\CorkUnitTests\\camera.xml");
      double time = 16;

      SECTION("test applyforce gravity only") {
        MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &time, entity->getMessageHandler(APPLY_FORCE_MESSAGE)));

        Particle* data = (Particle*) entity->getDataComponent(PARTICLE_COMPONENT)->getData();

        REQUIRE(data->totalForce.getX() == approx(0.0f));
        REQUIRE(data->totalForce.getY() == approx(0.0f));
        REQUIRE(data->totalForce.getZ() == approx(0.0f));
        REQUIRE(data->acceleration.getX() == approx(0.0f));
        REQUIRE(data->acceleration.getY() == approx(-0.918f));
        REQUIRE(data->acceleration.getZ() == approx(0.0f));
        REQUIRE(data->velocity.getX() == approx(0.0f));
        REQUIRE(data->velocity.getY() == approx(-0.01469f));
        REQUIRE(data->velocity.getZ() == approx(0.0f));
        REQUIRE(data->displacement.getX() == approx(0.0f));
        REQUIRE(data->displacement.getY() == approx(-0.00012f));
        REQUIRE(data->displacement.getZ() == approx(0.0f));
      }

      SECTION("test applyforce no force") {
        Particle* data = (Particle*) entity->getDataComponent(PARTICLE_COMPONENT)->getData();
        data->gravityEnabled = false;

        MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &time, entity->getMessageHandler(APPLY_FORCE_MESSAGE)));

        REQUIRE(data->totalForce.getX() == approx(0.0f));
        REQUIRE(data->totalForce.getY() == approx(0.0f));
        REQUIRE(data->totalForce.getZ() == approx(0.0f));
        REQUIRE(data->acceleration.getX() == approx(0.0f));
        REQUIRE(data->acceleration.getY() == approx(0.0f));
        REQUIRE(data->acceleration.getZ() == approx(0.0f));
        REQUIRE(data->velocity.getX() == approx(0.0f));
        REQUIRE(data->velocity.getY() == approx(0.0f));
        REQUIRE(data->velocity.getZ() == approx(0.0f));
        REQUIRE(data->displacement.getX() == approx(0.0f));
        REQUIRE(data->displacement.getY() == approx(0.0f));
        REQUIRE(data->displacement.getZ() == approx(0.0f));
      }

      SECTION("test applyforce gravity and external force") {
        Particle* data = (Particle*) entity->getDataComponent(PARTICLE_COMPONENT)->getData();
        data->totalForce += Vector3(0.0f, 0.0f, -1.0f);

        MessageHandler::forwardMessage(Message(APPLY_FORCE_MESSAGE, &time, entity->getMessageHandler(APPLY_FORCE_MESSAGE)));

        REQUIRE(data->totalForce.getX() == approx(0.0f));
        REQUIRE(data->totalForce.getY() == approx(0.0f));
        REQUIRE(data->totalForce.getZ() == approx(0.0f));
        REQUIRE(data->acceleration.getX() == approx(0.0f));
        REQUIRE(data->acceleration.getY() == approx(-0.918f));
        REQUIRE(data->acceleration.getZ() == approx(-1.0f));
        REQUIRE(data->velocity.getX() == approx(0.0f));
        REQUIRE(data->velocity.getY() == approx(-0.01469f));
        REQUIRE(data->velocity.getZ() == approx(-0.016f));
        REQUIRE(data->displacement.getX() == approx(0.0f));
        REQUIRE(data->displacement.getY() == approx(-0.00012f));
        REQUIRE(data->displacement.getZ() == approx(-0.00013f));
      }

      EntityLoader::cleanup();
      ServiceLocator::cleanup();
    }
  }
}