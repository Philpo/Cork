#include "stdafx.h"
#include "catch.hpp"
#include "GameObject.h"
#include "ApplyForceComponent.h"
#include "TransformComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace gameobject {
    TEST_CASE("test addMessageHandler") {
      GameObject go;
      IComponent* c = new ApplyForceComponent();
      size_t type = std::hash<string>{}("test");
      go.addMessageHandler (type, c);
      REQUIRE((go.getMessageHandler(type) != nullptr));
      REQUIRE(typeid(*go.getMessageHandler(type)) == typeid(*c));
      REQUIRE(go.getSupportedMessages().size() == 1);
      REQUIRE(go.getSupportedMessages()[0] == type);
      delete c;
    }

    TEST_CASE("test getMessageHandler") {
      GameObject go;
      size_t type = std::hash<string>{}("test");
      REQUIRE((go.getMessageHandler(type) == nullptr));
    }

    TEST_CASE("test addDataComponent") {
      GameObject go;
      IDataComponent* c = new TransformComponent;
      size_t type = std::hash<string>{}("test");
      go.addDataComponent(type, c);
      REQUIRE((go.getDataComponent(type) != nullptr));
      REQUIRE(typeid(*go.getDataComponent(type)) == typeid(*c));
      delete c;
    }

    TEST_CASE("test getDataComponent") {
      GameObject go;
      size_t type = std::hash<string>{}("test");
      REQUIRE((go.getDataComponent(type) == nullptr));
    }
  }
}