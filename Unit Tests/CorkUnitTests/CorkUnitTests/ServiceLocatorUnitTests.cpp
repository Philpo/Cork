#include "stdafx.h"
#include "catch.hpp"
#include "ServiceLocator.h"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace servicelocator {
    Factory factory = Factory::getFactory();

    TEST_CASE("test service locator getComponent") {
      SECTION("test mapped component") {
        ServiceLocator::addFactoryFunction("a", std::bind(&Factory::getBasicGraphicsComponent, factory));
        IComponent* c = ServiceLocator::getComponent("a");
        REQUIRE((c != nullptr));
        REQUIRE(typeid(*c) == typeid(ConsoleGraphicsComponent));
        ServiceLocator::cleanup();
      }
      SECTION("test unmapped component") {
        IComponent* c = ServiceLocator::getComponent("b");
        REQUIRE((c == nullptr));
      }
    }

    TEST_CASE("test deleteComponent") {
      ServiceLocator::addFactoryFunction(GRAPHICS_COMPONENT, std::bind(&Factory::getBasicGraphicsComponent, factory));
      IComponent* c = ServiceLocator::getComponent(GRAPHICS_COMPONENT);
      ServiceLocator::deleteComponent(c);
      REQUIRE((c == nullptr));

      c = new ConsoleGraphicsComponent;
      ServiceLocator::deleteComponent(c);
      REQUIRE((c != nullptr));
      delete c;
    }
  }
}