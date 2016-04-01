#include "stdafx.h"
#include "catch.hpp"
#include "ParticleComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace particlecomponent {
    TEST_CASE("test particle getData") {
      ParticleComponent c;
      REQUIRE((c.getData() != nullptr));
      Particle data = *(Particle*) c.getData();
      REQUIRE(data.totalForce.getX() == approx(0.0f));
      REQUIRE(data.totalForce.getY() == approx(0.0f));
      REQUIRE(data.totalForce.getZ() == approx(0.0f));
      REQUIRE(data.acceleration.getX() == approx(0.0f));
      REQUIRE(data.acceleration.getY() == approx(0.0f));
      REQUIRE(data.acceleration.getZ() == approx(0.0f));
      REQUIRE(data.velocity.getX() == approx(0.0f));
      REQUIRE(data.velocity.getY() == approx(0.0f));
      REQUIRE(data.velocity.getZ() == approx(0.0f));
      REQUIRE(data.displacement.getX() == approx(0.0f));
      REQUIRE(data.displacement.getY() == approx(0.0f));
      REQUIRE(data.displacement.getZ() == approx(0.0f));
      REQUIRE(data.mass == approx(0.0f));
      REQUIRE(data.maxSpeed == approx(0.0f));
      REQUIRE(data.gravityEnabled);
    }

    TEST_CASE("test particle setData") {
      ParticleComponent c;
      Particle data = *(Particle*) c.getData();
      data.totalForce.setX(1.0f);
      data.totalForce.setY(1.5f);
      data.totalForce.setZ(2.0f);
      data.acceleration.setX(1.0f);
      data.acceleration.setY(1.5f);
      data.acceleration.setZ(2.0f);
      data.velocity.setX(1.0f);
      data.velocity.setY(1.5f);
      data.velocity.setZ(2.0f);
      data.displacement.setX(1.0f);
      data.displacement.setY(1.5f);
      data.displacement.setZ(2.0f);
      data.mass = 1.0f;
      data.maxSpeed = 1.5f;
      data.gravityEnabled = false;
      c.setData(&data);

      data = *(Particle*) c.getData();
      REQUIRE(data.totalForce.getX() == approx(1.0f));
      REQUIRE(data.totalForce.getY() == approx(1.5f));
      REQUIRE(data.totalForce.getZ() == approx(2.0f));
      REQUIRE(data.acceleration.getX() == approx(1.0f));
      REQUIRE(data.acceleration.getY() == approx(1.5f));
      REQUIRE(data.acceleration.getZ() == approx(2.0f));
      REQUIRE(data.velocity.getX() == approx(1.0f));
      REQUIRE(data.velocity.getY() == approx(1.5f));
      REQUIRE(data.velocity.getZ() == approx(2.0f));
      REQUIRE(data.displacement.getX() == approx(1.0f));
      REQUIRE(data.displacement.getY() == approx(1.5f));
      REQUIRE(data.displacement.getZ() == approx(2.0f));
      REQUIRE(data.mass == approx(1.0f));
      REQUIRE(data.maxSpeed == approx(1.5f));
      REQUIRE(!data.gravityEnabled);
    }
  }
}