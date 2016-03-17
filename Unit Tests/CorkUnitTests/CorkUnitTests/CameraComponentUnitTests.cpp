#include "stdafx.h"
#include "catch.hpp"
#include "CameraComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace cameracomponent {
    TEST_CASE("test camera getData") {
      CameraComponent c;
      REQUIRE((c.getData() != nullptr));
      Camera data = *(Camera*) c.getData();
      REQUIRE(data.position.getX() == approx(0.0f));
      REQUIRE(data.position.getY() == approx(0.0f));
      REQUIRE(data.position.getZ() == approx(0.0f));
      REQUIRE(data.look.getX() == approx(0.0f));
      REQUIRE(data.look.getY() == approx(0.0f));
      REQUIRE(data.look.getZ() == approx(0.0f));
      REQUIRE(data.right.getX() == approx(0.0f));
      REQUIRE(data.right.getY() == approx(0.0f));
      REQUIRE(data.right.getZ() == approx(0.0f));
      REQUIRE(data.up.getX() == approx(0.0f));
      REQUIRE(data.up.getY() == approx(0.0f));
      REQUIRE(data.up.getZ() == approx(0.0f));
    }

    TEST_CASE("test camera setData") {
      CameraComponent c;
      Camera data = *(Camera*) c.getData();
      data.position.setX(1.0f);
      data.position.setY(1.5f);
      data.position.setZ(2.0f);
      data.look.setX(1.0f);
      data.look.setY(1.5f);
      data.look.setZ(2.0f);
      data.right.setX(1.0f);
      data.right.setY(1.5f);
      data.right.setZ(2.0f);
      data.up.setX(1.0f);
      data.up.setY(1.5f);
      data.up.setZ(2.0f);
      c.setData(&data);

      data = *(Camera*) c.getData();
      REQUIRE(data.position.getX() == approx(1.0f));
      REQUIRE(data.position.getY() == approx(1.5f));
      REQUIRE(data.position.getZ() == approx(2.0f));
      REQUIRE(data.look.getX() == approx(1.0f));
      REQUIRE(data.look.getY() == approx(1.5f));
      REQUIRE(data.look.getZ() == approx(2.0f));
      REQUIRE(data.right.getX() == approx(1.0f));
      REQUIRE(data.right.getY() == approx(1.5f));
      REQUIRE(data.right.getZ() == approx(2.0f));
      REQUIRE(data.up.getX() == approx(1.0f));
      REQUIRE(data.up.getY() == approx(1.5f));
      REQUIRE(data.up.getZ() == approx(2.0f));
    }
  }
}