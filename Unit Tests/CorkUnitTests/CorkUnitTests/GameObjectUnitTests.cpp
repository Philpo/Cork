#include "stdafx.h"
#include "catch.hpp"
#include "GameObject.h"
#include "ApplyForceComponent.h"
#include "TransformComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace gameobject {
    TEST_CASE("test addComponent") {
      GameObject go;
      IComponent* c = new ApplyForceComponent();
      go.addComponent("test", c);
      REQUIRE((go.getMessageHandler("test") != nullptr));
      REQUIRE(typeid(*go.getMessageHandler("test")) == typeid(*c));
      REQUIRE(go.getSupportedMessages().size() == 1);
      REQUIRE(go.getSupportedMessages()[0] == "test");
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