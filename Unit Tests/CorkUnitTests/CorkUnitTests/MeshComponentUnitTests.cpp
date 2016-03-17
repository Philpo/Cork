#include "stdafx.h"
#include "catch.hpp"
#include "MeshComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace meshcomponent {
    TEST_CASE("test mesh getData") {
      MeshComponent c;
      REQUIRE((c.getData() != nullptr));
      int data = *(int*) c.getData();
      REQUIRE(data == -1);
    }

    TEST_CASE("test mesh setData") {
      MeshComponent c;
      int data = *(int*) c.getData();
      data = 1;
      c.setData(&data);

      data = *(int*) c.getData();
      REQUIRE(data == 1);
    }
  }
}