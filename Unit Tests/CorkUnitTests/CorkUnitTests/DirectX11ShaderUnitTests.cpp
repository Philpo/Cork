#include "stdafx.h"
#include "catch.hpp"
#include "DirectX11Shader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace directx11shader {
    TEST_CASE("test directx11shader constructor") {
      DirectX11Shader shader;

      REQUIRE((shader.getShader() == nullptr));
      REQUIRE(shader.getType() == "");
    }

    TEST_CASE("test directx11shader setters") {
      DirectX11Shader shader;

      shader.setType("test");
      REQUIRE(shader.getType() == "test");
    }
  }
}