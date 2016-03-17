#include "stdafx.h"
#include "catch.hpp"
#include "GameObject.h"
#include "BasicMovementComponent.h"
#include "TransformComponent.h"
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

    TEST_CASE("test getComponent") {
      GameObject go;
      REQUIRE((go.getMessageHandler("test") == nullptr));
    }

    TEST_CASE("test addDataComponent") {
      GameObject go;
      IDataComponent* c = new TransformComponent;
      go.addDataComponent("test", c);
      REQUIRE((go.getDataComponent("test") != nullptr));
      REQUIRE(typeid(*go.getDataComponent("test")) == typeid(*c));
      delete c;
    }

    TEST_CASE("test getDataComponent") {
      GameObject go;
      REQUIRE((go.getDataComponent("test") == nullptr));
    }
  }
}