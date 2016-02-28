#include "stdafx.h"
#include "catch.hpp"
#include "GameObject.h"
#include "BasicMovementComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace gameobject {
    TEST_CASE("test go constructors") {
      SECTION("test default constructor") {
        GameObject go;
        REQUIRE(go.getPositon().getX() == approx(0.0f));
        REQUIRE(go.getPositon().getY() == approx(0.0f));
        REQUIRE(go.getPositon().getZ() == approx(0.0f));
      }
      SECTION("test paramterised constructor") {
        GameObject go(Vector3<float>(1.0f, 2.0f, 3.0f));
        REQUIRE(go.getPositon().getX() == approx(1.0f));
        REQUIRE(go.getPositon().getY() == approx(2.0f));
        REQUIRE(go.getPositon().getZ() == approx(3.0f));
      }
    }

    TEST_CASE("test setPosition") {
      GameObject go;
      go.setPosition(Vector3<float>(1.0f, 2.0f, 3.0f));
      REQUIRE(go.getPositon().getX() == approx(1.0f));
      REQUIRE(go.getPositon().getY() == approx(2.0f));
      REQUIRE(go.getPositon().getZ() == approx(3.0f));
    }

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