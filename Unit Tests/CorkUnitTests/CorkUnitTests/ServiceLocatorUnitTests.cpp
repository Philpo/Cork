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
        ServiceLocator::addMessageHandlerFunction("a", std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
        IComponent* c = ServiceLocator::getMessageHandler("a");
        REQUIRE((c != nullptr));
        REQUIRE(typeid(*c) == typeid(TestInputComponent));
        ServiceLocator::cleanup();
      }
      SECTION("test unmapped component") {
        IComponent* c = ServiceLocator::getMessageHandler("b");
        REQUIRE((c == nullptr));
      }
    }

    TEST_CASE("test deleteComponent") {
      ServiceLocator::addMessageHandlerFunction(INPUT_COMPONENT, std::bind(&Factory::getBasicInputComponent, factory, std::placeholders::_1));
      IComponent* c = ServiceLocator::getMessageHandler(INPUT_COMPONENT);
      ServiceLocator::deleteMessageHandler(c);
      REQUIRE((c == nullptr));

      c = new JumpComponent;
      ServiceLocator::deleteMessageHandler(c);
      REQUIRE((c != nullptr));
      delete c;
    }
  }
}