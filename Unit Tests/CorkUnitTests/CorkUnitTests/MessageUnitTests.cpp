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
        REQUIRE(m.getType() == "");
        REQUIRE((m.getData() == nullptr));
        REQUIRE((m.getTarget() == nullptr));
      }
      SECTION("test parameterised constructor") {
        int data = 1;
        GameObject* go = new GameObject;
        Message m("test", &data, go);
        REQUIRE(m.getType() == "test");
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
        m.setType("a");
        REQUIRE(m.getType() == "a");
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