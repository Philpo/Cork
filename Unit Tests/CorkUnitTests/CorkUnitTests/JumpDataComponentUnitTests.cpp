#include "stdafx.h"
#include "catch.hpp"
#include "JumpDataComponent.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace jumpdatacomponent {
    TEST_CASE("test jumpdata getData") {
      JumpDataComponent c;
      REQUIRE((c.getData() != nullptr));
      JumpData data = *(JumpData*) c.getData();
      REQUIRE(data.maxJumpTime == approx(0.0f));
      REQUIRE(data.jumpForce == approx(0.0f));
      REQUIRE(data.jumpControlPower == approx(0.0f));
      REQUIRE(data.jumpTime == approx(0.0f));
      REQUIRE(!data.jumping);
      REQUIRE(!data.falling);
    }

    TEST_CASE("test jumpdata setData") {
      JumpDataComponent c;
      JumpData data = *(JumpData*) c.getData();
      data.maxJumpTime = 1.0f;
      data.jumpControlPower = 1.5f;
      data.jumpForce = 2.0f;
      data.jumpTime = 2.5f;
      data.falling = true;
      data.jumping = true;
      c.setData(&data);

      data = *(JumpData*) c.getData();
      REQUIRE(data.maxJumpTime == approx(1.0f));
      REQUIRE(data.jumpForce == approx(2.0f));
      REQUIRE(data.jumpControlPower == approx(1.5f));
      REQUIRE(data.jumpTime == approx(2.5f));
      REQUIRE(data.jumping);
      REQUIRE(data.falling);
    }
  }
}