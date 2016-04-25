#include "stdafx.h"
#include "catch.hpp"
#include "TransformComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace transformcomponent {
    TEST_CASE("test transform getData") {
      TransformComponent c;
      REQUIRE((c.getData() != nullptr));
      Transform data = *(Transform*) c.getData();
      REQUIRE(data.position.getX() == approx(0.0f));
      REQUIRE(data.position.getY() == approx(0.0f));
      REQUIRE(data.position.getZ() == approx(0.0f));
      REQUIRE(data.previousPosition.getX() == approx(0.0f));
      REQUIRE(data.previousPosition.getY() == approx(0.0f));
      REQUIRE(data.previousPosition.getZ() == approx(0.0f));
      REQUIRE(data.localRotation.getX() == approx(0.0f));
      REQUIRE(data.localRotation.getY() == approx(0.0f));
      REQUIRE(data.localRotation.getZ() == approx(0.0f));
      REQUIRE(data.scale.getX() == approx(0.0f));
      REQUIRE(data.scale.getY() == approx(0.0f));
      REQUIRE(data.scale.getZ() == approx(0.0f));
      REQUIRE(data.worldRotation.getX() == approx(0.0f));
      REQUIRE(data.worldRotation.getY() == approx(0.0f));
      REQUIRE(data.worldRotation.getZ() == approx(0.0f));
      REQUIRE((data.parent == nullptr));
    }

    TEST_CASE("test transform setData") {
      TransformComponent c;
      Transform data = *(Transform*) c.getData();
      Transform parent;
      data.position.setX(1.0f);
      data.position.setY(1.5f);
      data.position.setZ(2.0f);
      data.previousPosition.setX(1.0f);
      data.previousPosition.setY(1.5f);
      data.previousPosition.setZ(2.0f);
      data.localRotation.setX(1.0f);
      data.localRotation.setY(1.5f);
      data.localRotation.setZ(2.0f);
      data.scale.setX(1.0f);
      data.scale.setY(1.5f);
      data.scale.setZ(2.0f);
      data.worldRotation.setX(1.0f);
      data.worldRotation.setY(1.5f);
      data.worldRotation.setZ(2.0f);
      data.parent = &parent;
      c.setData(&data);

      data = *(Transform*) c.getData();
      REQUIRE(data.position.getX() == approx(1.0f));
      REQUIRE(data.position.getY() == approx(1.5f));
      REQUIRE(data.position.getZ() == approx(2.0f));
      REQUIRE(data.previousPosition.getX() == approx(1.0f));
      REQUIRE(data.previousPosition.getY() == approx(1.5f));
      REQUIRE(data.previousPosition.getZ() == approx(2.0f));
      REQUIRE(data.localRotation.getX() == approx(1.0f));
      REQUIRE(data.localRotation.getY() == approx(1.5f));
      REQUIRE(data.localRotation.getZ() == approx(2.0f));
      REQUIRE(data.scale.getX() == approx(1.0f));
      REQUIRE(data.scale.getY() == approx(1.5f));
      REQUIRE(data.scale.getZ() == approx(2.0f));
      REQUIRE(data.worldRotation.getX() == approx(1.0f));
      REQUIRE(data.worldRotation.getY() == approx(1.5f));
      REQUIRE(data.worldRotation.getZ() == approx(2.0f));
      REQUIRE((data.parent == &parent));
    }
  }
}