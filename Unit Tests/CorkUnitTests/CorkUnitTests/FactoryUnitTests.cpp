#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace factory {
    Factory factory;

    TEST_CASE("test factory functions") {
      IComponent* component = factory.getBasicGraphicsComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(ConsoleGraphicsComponent));
      delete component;

      component = factory.getBasicInputComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(TestInputComponent));
      delete component;

      component = factory.getBasicMovementComponent(nullptr);
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(BasicMovementComponent));
      delete component;
    }
  }
}