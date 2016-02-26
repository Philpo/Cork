#include "stdafx.h"
#include "catch.hpp"
#include "Utils.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  TEST_CASE("test string conversion functions") {
    SECTION("test int conversion") {
      SECTION("test positive int") {
        REQUIRE(convertStringToNumber<int>("1") == 1);
      }
      SECTION("test negative int") {
        REQUIRE(convertStringToNumber<int>("-1") == -1);
      }
      SECTION("test zero int") {
        REQUIRE(convertStringToNumber<int>("0") == 0);
      }
    }

    SECTION("test float conversion") {
      SECTION("test positive float") {
        REQUIRE(convertStringToNumber<float>("1.5") == approx(1.5f));
      }
      SECTION("test negative float") {
        REQUIRE(convertStringToNumber<float>("-1.5") == approx(-1.5f));
      }
      SECTION("test zero float") {
        REQUIRE(convertStringToNumber<float>("0.0") == approx(0.0f));
      }
    }
  }
}