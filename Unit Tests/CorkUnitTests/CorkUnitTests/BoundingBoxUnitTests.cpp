#include "stdafx.h"
#include "catch.hpp"
#include "BoundingBoxComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace boundingboxcomponent {
    TEST_CASE("test boundingbox getData") {
      BoundingBoxComponent c;
      REQUIRE((c.getData() != nullptr));
      BoundingBox data = *(BoundingBox*) c.getData();
      REQUIRE(data.centre.getX() == approx(0.0f));
      REQUIRE(data.centre.getY() == approx(0.0f));
      REQUIRE(data.centre.getZ() == approx(0.0f));
      REQUIRE(data.height == approx(0.0f));
      REQUIRE(data.width == approx(0.0f));
      REQUIRE(data.depth == approx(0.0f));
    }

    TEST_CASE("test boundingbox setData") {
      BoundingBoxComponent c;
      BoundingBox data = *(BoundingBox*) c.getData();
      data.centre.setX(1.0f);
      data.centre.setY(1.5f);
      data.centre.setZ(2.0f);
      data.height = 1.0f;
      data.width = 1.5f;
      data.depth = 2.0f;
      c.setData(&data);

      data = *(BoundingBox*) c.getData();
      REQUIRE(data.centre.getX() == approx(1.0f));
      REQUIRE(data.centre.getY() == approx(1.5f));
      REQUIRE(data.centre.getZ() == approx(2.0f));
      REQUIRE(data.height == approx(1.0f));
      REQUIRE(data.width == approx(1.5f));
      REQUIRE(data.depth == approx(2.0f));
    }
  }
}