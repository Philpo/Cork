#include "stdafx.h"
#include "catch.hpp"
#include "GameObject.h"
#include "BasicMovementComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace gameobject {
    TEST_CASE("test addComponent") {
      GameObject go;
      IComponent* c = new BasicMovementComponent();
      go.addComponent("test", c);
      REQUIRE((go.getMessageHandler("test") != nullptr));
      REQUIRE(typeid(*go.getMessageHandler("test")) == typeid(*c));
      delete c;
    }

    TEST_CASE("test game object getComponent") {
      GameObject go;
      REQUIRE((go.getMessageHandler("test") == nullptr));
    }
  }
}