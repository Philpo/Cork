#include "stdafx.h"
#include "catch.hpp"
#include "DirectX11ConstantBuffer.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace directx11constantbuffer {
    TEST_CASE("test directx11constantbuffer constructor") {
      DirectX11ConstantBuffer cb(10);
      REQUIRE((cb.getData() != nullptr));
      REQUIRE(cb.getSizeInBytes() == 10);
    }

    TEST_CASE("test directx11constantbuffer addMatrix") {
      DirectX11ConstantBuffer cb(64);
      cb.addMatrix("test", &XMMatrixIdentity());

      XMMATRIX data = *(XMMATRIX*) cb.getData();
      XMFLOAT4X4 matrix;
      XMStoreFloat4x4(&matrix, data);
      REQUIRE(matrix._11 == approx(1.0f));
      REQUIRE(matrix._12 == approx(0.0f));
      REQUIRE(matrix._13 == approx(0.0f));
      REQUIRE(matrix._14 == approx(0.0f));
      REQUIRE(matrix._21 == approx(0.0f));
      REQUIRE(matrix._22 == approx(1.0f));
      REQUIRE(matrix._23 == approx(0.0f));
      REQUIRE(matrix._24 == approx(0.0f));
      REQUIRE(matrix._31 == approx(0.0f));
      REQUIRE(matrix._32 == approx(0.0f));
      REQUIRE(matrix._33 == approx(1.0f));
      REQUIRE(matrix._34 == approx(0.0f));
      REQUIRE(matrix._41 == approx(0.0f));
      REQUIRE(matrix._42 == approx(0.0f));
      REQUIRE(matrix._43 == approx(0.0f));
      REQUIRE(matrix._44 == approx(1.0f));
    }

    TEST_CASE("test directx11constantbuffer addFloat2") {
      DirectX11ConstantBuffer cb(8);
      cb.addFloat2("test", &XMFLOAT2 { 0.0f, 0.0f });

      XMFLOAT2 data = *(XMFLOAT2*) cb.getData();
      REQUIRE(data.x == approx(0.0f));
      REQUIRE(data.y == approx(0.0f));
    }

    TEST_CASE("test directx11constantbuffer addFloat3") {
      DirectX11ConstantBuffer cb(12);
      cb.addFloat3("test", &XMFLOAT3 { 0.0f, 0.0f, 0.0f });

      XMFLOAT3 data = *(XMFLOAT3*) cb.getData();
      REQUIRE(data.x == approx(0.0f));
      REQUIRE(data.y == approx(0.0f));
      REQUIRE(data.z == approx(0.0f));
    }

    TEST_CASE("test directx11constantbuffer addFloat4") {
      DirectX11ConstantBuffer cb(16);
      cb.addFloat4("test", &XMFLOAT4 { 0.0f, 0.0f, 0.0f, 0.0f });

      XMFLOAT4 data = *(XMFLOAT4*) cb.getData();
      REQUIRE(data.x == approx(0.0f));
      REQUIRE(data.y == approx(0.0f));
      REQUIRE(data.z == approx(0.0f));
      REQUIRE(data.w == approx(0.0f));
    }

    TEST_CASE("test directx11constantbuffer addLight") {
      DirectX11ConstantBuffer cb(sizeof(LightStruct));
      cb.addLight("test", &LightStruct());

      LightStruct data = *(LightStruct*) cb.getData();
      REQUIRE(data.ambient.x == approx(0.0f));
      REQUIRE(data.ambient.y == approx(0.0f));
      REQUIRE(data.ambient.z == approx(0.0f));
      REQUIRE(data.ambient.w == approx(0.0f));
      REQUIRE(data.diffuse.x == approx(0.0f));
      REQUIRE(data.diffuse.y == approx(0.0f));
      REQUIRE(data.diffuse.z == approx(0.0f));
      REQUIRE(data.diffuse.w == approx(0.0f));
      REQUIRE(data.specular.x == approx(0.0f));
      REQUIRE(data.specular.y == approx(0.0f));
      REQUIRE(data.specular.z == approx(0.0f));
      REQUIRE(data.specular.w == approx(0.0f));
      REQUIRE(data.position.x == approx(0.0f));
      REQUIRE(data.position.y == approx(0.0f));
      REQUIRE(data.position.z == approx(0.0f));
      REQUIRE(data.direction.x == approx(0.0f));
      REQUIRE(data.direction.y == approx(0.0f));
      REQUIRE(data.direction.z == approx(0.0f));
      REQUIRE(data.attenuation.x == approx(0.0f));
      REQUIRE(data.attenuation.y == approx(0.0f));
      REQUIRE(data.attenuation.z == approx(0.0f));
      REQUIRE(data.range == approx(0.0f));
      REQUIRE(data.exponent == approx(0.0f));
      REQUIRE(data.enabled == 1);
    }

    TEST_CASE("test directx11constantbuffer addMaterial") {
      DirectX11ConstantBuffer cb(sizeof(Material));
      cb.addMaterial("test", &Material());

      Material data = *(Material*) cb.getData();
      REQUIRE(data.ambient.x == approx(0.0f));
      REQUIRE(data.ambient.y == approx(0.0f));
      REQUIRE(data.ambient.z == approx(0.0f));
      REQUIRE(data.ambient.w == approx(0.0f));
      REQUIRE(data.diffuse.x == approx(0.0f));
      REQUIRE(data.diffuse.y == approx(0.0f));
      REQUIRE(data.diffuse.z == approx(0.0f));
      REQUIRE(data.diffuse.w == approx(0.0f));
      REQUIRE(data.specular.x == approx(0.0f));
      REQUIRE(data.specular.y == approx(0.0f));
      REQUIRE(data.specular.z == approx(0.0f));
      REQUIRE(data.specular.w == approx(0.0f));
      REQUIRE(data.specularPower == approx(0.0f));
    }

    TEST_CASE("test directx11constantbuffer addFloat") {
      DirectX11ConstantBuffer cb(4);
      cb.addFloat("test", 0.0f);

      float data = *(float*) cb.getData();
      REQUIRE(data == approx(0.0f));
    }

    TEST_CASE("test directx11constantbuffer addInt") {
      DirectX11ConstantBuffer cb(4);
      cb.addInt("test", 0);

      int data = *(int*) cb.getData();
      REQUIRE(data == 0);
    }

    TEST_CASE("test directx11constantbuffer buffer overflow") {
      DirectX11ConstantBuffer cb(1);

      REQUIRE_THROWS(cb.addMatrix("test", &XMMatrixIdentity()));
      REQUIRE_THROWS(cb.addFloat2("test", &XMFLOAT2()));
      REQUIRE_THROWS(cb.addFloat3("test", &XMFLOAT3()));
      REQUIRE_THROWS(cb.addFloat4("test", &XMFLOAT4()));
      REQUIRE_THROWS(cb.addLight("test", &LightStruct()));
      REQUIRE_THROWS(cb.addMaterial("test", &Material()));
      REQUIRE_THROWS(cb.addFloat("test", 1.0f));
      REQUIRE_THROWS(cb.addInt("test", 1));
    }

    //TODO test update methods
  }
}