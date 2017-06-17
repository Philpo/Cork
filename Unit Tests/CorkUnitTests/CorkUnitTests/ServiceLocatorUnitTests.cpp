#include "stdafx.h"
#include "catch.hpp"
#include "ServiceLocator.h"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace servicelocator {
    Factory factory;

    TEST_CASE("test service locator getComponent") {
      SECTION("test mapped component") {
        size_t type = std::hash<string>{}("a");
        ServiceLocator::addMessageHandlerFunction(type, std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
        IComponent* c = ServiceLocator::getMessageHandler(type);
        REQUIRE((c != nullptr));
        REQUIRE(typeid(*c) == typeid(TestInputComponent));
        ServiceLocator::cleanup();
      }
      SECTION("test unmapped component") {
        INFO("test");
        size_t type = std::hash<string>{}("b");
        IComponent* c = ServiceLocator::getMessageHandler(type);
        REQUIRE((c == nullptr));
      }
    }

    TEST_CASE("test deleteComponent") {
      ServiceLocator::addMessageHandlerFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
      IComponent* c = ServiceLocator::getMessageHandler(INPUT_COMPONENT);
      ServiceLocator::deleteMessageHandler(c);
      REQUIRE((c == nullptr));

      c = new ApplyForceComponent;
      ServiceLocator::deleteMessageHandler(c);
      REQUIRE((c != nullptr));
      delete c;
    }
  }
}