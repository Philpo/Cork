#include "stdafx.h"
#include "catch.hpp"
#include "BinaryData.h"
#include "TypeDefs.h"
#include "DirectX11TypeDefs.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace binarydata {
    struct LightStruct {
      LightStruct() : range(0.0f), exponent(0.0f), enabled(1) {
        ambient = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
        diffuse = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
        specular = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
        position = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
        direction = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
        attenuation = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
      }

      XMFLOAT4 ambient;
      XMFLOAT4 diffuse;
      XMFLOAT4 specular;
      XMFLOAT3 position;
      float range;
      XMFLOAT3 direction;
      float exponent;
      XMFLOAT3 attenuation;
      int enabled;
      int type;
      XMFLOAT3 padding;
    };

    struct Material {
      Material() : specularPower(0.0f) {
        ambient = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
        diffuse = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
        specular = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
      }

      XMFLOAT4 ambient, diffuse, specular;
      float specularPower;
    };

    TEST_CASE("test binarydata constructor") {
      BinaryData cb(10);
      REQUIRE((cb.getData() != nullptr));
      REQUIRE(cb.getSizeInBytes() == 10);
    }

    TEST_CASE("test binarydata addData") {
      SECTION("test adding XMMATRIX") {
        BinaryData cb(64);
        cb.addData("test", XMMatrixIdentity());

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

      SECTION("test adding LightStruct") {
        BinaryData cb(sizeof(LightStruct));
        cb.addData("test", LightStruct());

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
    }

    TEST_CASE("test binarydata buffer overflow") {
      BinaryData cb(1);

      REQUIRE_THROWS(cb.addData("test", XMMatrixIdentity()));
      REQUIRE_THROWS(cb.addData("test", XMFLOAT2()));
      REQUIRE_THROWS(cb.addData("test", XMFLOAT3()));
      REQUIRE_THROWS(cb.addData("test", XMFLOAT4()));
      REQUIRE_THROWS(cb.addData("test", LightStruct()));
      REQUIRE_THROWS(cb.addData("test", Material()));
    }

    TEST_CASE("test binarydata updateData") {
      SECTION("test update XMMATRIX") {
        BinaryData cb(64);
        cb.addData("test", XMMatrixIdentity());
        cb.updateData("test", XMMatrixTranslation(1.0f, 2.0f, 3.0f));

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
        REQUIRE(matrix._41 == approx(1.0f));
        REQUIRE(matrix._42 == approx(2.0f));
        REQUIRE(matrix._43 == approx(3.0f));
        REQUIRE(matrix._44 == approx(1.0f));
      }

      SECTION("test updating LightStruct") {
        BinaryData cb(sizeof(LightStruct));
        LightStruct light;
        cb.addData("test", light);
        light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
        cb.updateData("test", light);

        LightStruct data = *(LightStruct*) cb.getData();
        REQUIRE(data.ambient.x == approx(0.2f));
        REQUIRE(data.ambient.y == approx(0.2f));
        REQUIRE(data.ambient.z == approx(0.2f));
        REQUIRE(data.ambient.w == approx(1.0f));
      }
    }

    TEST_CASE("test binarydata addVariable") {
      SECTION("test adding XMMATRIX") {
        BinaryData cb(64);
        cb.addVariable("test", sizeof(XMMATRIX));
        cb.updateData("test", XMMatrixTranslation(1.0f, 2.0f, 3.0f));

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
        REQUIRE(matrix._41 == approx(1.0f));
        REQUIRE(matrix._42 == approx(2.0f));
        REQUIRE(matrix._43 == approx(3.0f));
        REQUIRE(matrix._44 == approx(1.0f));
      }

      SECTION("test adding LightStruct") {
        BinaryData cb(sizeof(LightStruct));
        LightStruct light;
        cb.addVariable("test", sizeof(light));
        light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
        cb.updateData("test", light);

        LightStruct data = *(LightStruct*) cb.getData();
        REQUIRE(data.ambient.x == approx(0.2f));
        REQUIRE(data.ambient.y == approx(0.2f));
        REQUIRE(data.ambient.z == approx(0.2f));
        REQUIRE(data.ambient.w == approx(1.0f));
      }
    }

    TEST_CASE("test binarydata getVariable") {
      BinaryData cb(64 + sizeof(LightStruct));
      cb.addVariable("test", sizeof(XMMATRIX));
      cb.updateData("test", XMMatrixTranslation(1.0f, 2.0f, 3.0f));

      XMMATRIX data = *cb.getVariable<XMMATRIX>("test");
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
      REQUIRE(matrix._41 == approx(1.0f));
      REQUIRE(matrix._42 == approx(2.0f));
      REQUIRE(matrix._43 == approx(3.0f));
      REQUIRE(matrix._44 == approx(1.0f));

      LightStruct light;
      cb.addVariable("light", sizeof(light));
      light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
      cb.updateData("light", light);

      light = *cb.getVariable<LightStruct>("light");
      REQUIRE(light.ambient.x == approx(0.2f));
      REQUIRE(light.ambient.y == approx(0.2f));
      REQUIRE(light.ambient.z == approx(0.2f));
      REQUIRE(light.ambient.w == approx(1.0f));
    }
  }
}