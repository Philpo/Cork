#include "stdafx.h"
#include "catch.hpp"
#include "Message.h"
#include "GameObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace message {
    TEST_CASE("test message constructors") {
      SECTION("test default constructor") {
        Message m;
        REQUIRE(m.getType() == -1);
        REQUIRE((m.getData() == nullptr));
        REQUIRE((m.getTarget() == nullptr));
      }
      SECTION("test parameterised constructor") {
        int data = 1;
        GameObject* go = new GameObject;
        size_t type = std::hash<string>{}("test");
        Message m(type, &data, go);
        REQUIRE(m.getType() == type);
        REQUIRE((m.getData() != nullptr));
        REQUIRE(*((int*) m.getData()) == data);
        REQUIRE((m.getTarget() != nullptr));
        REQUIRE(m.getTarget() == go);
        delete go;
      }
    }

    TEST_CASE("test setters") {
      Message m;

      SECTION("test setType") {
        size_t type = std::hash<string>{}("a");
        m.setType(type);
        REQUIRE(m.getType() == type);
      }
      SECTION("test setData") {
        int data = 1;
        m.setData(&data);
        REQUIRE((m.getData() != nullptr));
        REQUIRE(*((int*) m.getData()) == data);
      }
      SECTION("test setTarget") {
        GameObject* go = new GameObject;
        m.setTarget(go);
        REQUIRE((m.getTarget() != nullptr));
        REQUIRE(m.getTarget() == go);
        delete go;
      }
    }
  }
}