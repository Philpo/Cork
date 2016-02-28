#include "stdafx.h"
#include "catch.hpp"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace factory {
    Factory factory = Factory::getFactory();

    TEST_CASE("test factory functions") {
      IComponent* component = factory.getBasicGraphicsComponent();
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(ConsoleGraphicsComponent));
      delete component;

      component = factory.getBasicInputComponent();
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(TestInputComponent));
      delete component;

      component = factory.getBasicMovementComponent();
      REQUIRE((component != nullptr));
      REQUIRE(typeid(*component) == typeid(BasicMovementComponent));
      delete component;
    }
  }
}