#include "stdafx.h"
#include "catch.hpp"
#include "ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace resourcemanager {
    TEST_CASE("test getTexture") {
      SECTION("test unloaded texture") {
        ITexture* tex = ResourceManager::getTexture(0);
        REQUIRE((tex == nullptr));
      }
    }

    TEST_CASE("test getMesh") {
      SECTION("test unloaded mesh") {
        Mesh* mesh = ResourceManager::getMesh(0);
        REQUIRE((mesh == nullptr));
      }
    }
  }
}