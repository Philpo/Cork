#include "stdafx.h"
#include "catch.hpp"
#include "DirectX11Vertex.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace directx11vertex {
    TEST_CASE("test directx11vertex constructor") {
      DirectX11Vertex v(10);
      REQUIRE((v.getData() != nullptr));
      REQUIRE(v.getSizeInBytes() == 10);
    }

    TEST_CASE("test directx11vertex addFloat2") {
      DirectX11Vertex v(8);
      XMFLOAT2 data { 1.0f, 2.0f };
      v.addFloat2(&data);

      data = *(XMFLOAT2*) v.getData();
      REQUIRE(data.x == approx(1.0f));
      REQUIRE(data.y == approx(2.0f));
    }

    TEST_CASE("test directx11vertex addFloat3") {
      DirectX11Vertex v(12);
      XMFLOAT3 data { 1.0f, 2.0f, 3.0f };
      v.addFloat3(&data);

      data = *(XMFLOAT3*) v.getData();
      REQUIRE(data.x == approx(1.0f));
      REQUIRE(data.y == approx(2.0f));
      REQUIRE(data.z == approx(3.0f));
    }

    TEST_CASE("test directx11vertex addFloat4") {
      DirectX11Vertex v(16);
      XMFLOAT4 data { 1.0f, 2.0f, 3.0f, 4.0f };
      v.addFloat4(&data);

      data = *(XMFLOAT4*) v.getData();
      REQUIRE(data.x == approx(1.0f));
      REQUIRE(data.y == approx(2.0f));
      REQUIRE(data.z == approx(3.0f));
      REQUIRE(data.w == approx(4.0f));
    }

    TEST_CASE("test directx11vertex buffer overflow") {
      DirectX11Vertex v(1);
      REQUIRE_THROWS(v.addFloat2(&XMFLOAT2()));
      REQUIRE_THROWS(v.addFloat3(&XMFLOAT3()));
      REQUIRE_THROWS(v.addFloat4(&XMFLOAT4()));
    }
  }
}