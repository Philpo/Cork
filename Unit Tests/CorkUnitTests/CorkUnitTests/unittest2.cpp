#include "stdafx.h"
#include "..\..\Catch-master\include\catch.hpp"
#include "..\..\..\src\Cork\Cork\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  TEST_CASE("test string conversion functions") {
    SECTION("test int conversion") {
      SECTION("test positive int") {
        REQUIRE(convertStringToNumber<int>("1") == 1);
      }
    }
  }
}