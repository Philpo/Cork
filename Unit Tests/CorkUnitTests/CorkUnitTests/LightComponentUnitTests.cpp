#include "stdafx.h"
#include "catch.hpp"
#include "LightComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace lightcomponent {
    TEST_CASE("test light getData") {
      LightComponent c;
      REQUIRE((c.getData() != nullptr));
      Light data = *(Light*) c.getData();
      REQUIRE(data.cbVariableName == "");
      REQUIRE(data.range == approx(0.0f));
      REQUIRE(data.exponent == approx(0.0f));
      REQUIRE(data.enabled == 1);
      REQUIRE(data.ambient.getX() == approx(0.0f));
      REQUIRE(data.ambient.getY() == approx(0.0f));
      REQUIRE(data.ambient.getZ() == approx(0.0f));
      REQUIRE(data.diffuse.getX() == approx(0.0f));
      REQUIRE(data.diffuse.getY() == approx(0.0f));
      REQUIRE(data.diffuse.getZ() == approx(0.0f));
      REQUIRE(data.specular.getX() == approx(0.0f));
      REQUIRE(data.specular.getY() == approx(0.0f));
      REQUIRE(data.specular.getZ() == approx(0.0f));
      REQUIRE(data.attenuation.getX() == approx(0.0f));
      REQUIRE(data.attenuation.getY() == approx(0.0f));
      REQUIRE(data.attenuation.getZ() == approx(0.0f));
      REQUIRE(data.position.getX() == approx(0.0f));
      REQUIRE(data.position.getY() == approx(0.0f));
      REQUIRE(data.position.getZ() == approx(0.0f));
      REQUIRE(data.direction.getX() == approx(0.0f));
      REQUIRE(data.direction.getY() == approx(0.0f));
      REQUIRE(data.direction.getZ() == approx(0.0f));
    }

    TEST_CASE("test light setData") {
      LightComponent c;
      Light data = *(Light*) c.getData();
      data.position.setX(1.0f);
      data.position.setY(1.5f);
      data.position.setZ(2.0f);
      data.ambient.setX(1.0f);
      data.ambient.setY(1.5f);
      data.ambient.setZ(2.0f);
      data.diffuse.setX(1.0f);
      data.diffuse.setY(1.5f);
      data.diffuse.setZ(2.0f);
      data.specular.setX(1.0f);
      data.specular.setY(1.5f);
      data.specular.setZ(2.0f);
      data.direction.setX(1.0f);
      data.direction.setY(1.5f);
      data.direction.setZ(2.0f);
      data.attenuation.setX(1.0f);
      data.attenuation.setY(1.5f);
      data.attenuation.setZ(2.0f);
      data.range = 1.0f;
      data.exponent = 1.0f;
      data.enabled = false;
      data.type = POINT_LIGHT;
      data.cbVariableName = "abcd";
      c.setData(&data);

      data = *(Light*) c.getData();
      REQUIRE(data.cbVariableName == "abcd");
      REQUIRE(data.range == approx(1.0f));
      REQUIRE(data.exponent == approx(1.0f));
      REQUIRE(data.enabled == false);
      REQUIRE(data.type == POINT_LIGHT);
      REQUIRE(data.ambient.getX() == approx(1.0f));
      REQUIRE(data.ambient.getY() == approx(1.5f));
      REQUIRE(data.ambient.getZ() == approx(2.0f));
      REQUIRE(data.diffuse.getX() == approx(1.0f));
      REQUIRE(data.diffuse.getY() == approx(1.5f));
      REQUIRE(data.diffuse.getZ() == approx(2.0f));
      REQUIRE(data.specular.getX() == approx(1.0f));
      REQUIRE(data.specular.getY() == approx(1.5f));
      REQUIRE(data.specular.getZ() == approx(2.0f));
      REQUIRE(data.attenuation.getX() == approx(1.0f));
      REQUIRE(data.attenuation.getY() == approx(1.5f));
      REQUIRE(data.attenuation.getZ() == approx(2.0f));
      REQUIRE(data.position.getX() == approx(1.0f));
      REQUIRE(data.position.getY() == approx(1.5f));
      REQUIRE(data.position.getZ() == approx(2.0f));
      REQUIRE(data.direction.getX() == approx(1.0f));
      REQUIRE(data.direction.getY() == approx(1.5f));
      REQUIRE(data.direction.getZ() == approx(2.0f));
    }
  }
}