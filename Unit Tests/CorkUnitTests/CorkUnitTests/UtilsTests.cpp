#include "stdafx.h"
#include "catch.hpp"
#include "Utils.h"
#include "TypeDefs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace utils {
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

      SECTION("test boolean conversion") {
        REQUIRE(convertStringToBool("true"));
        REQUIRE(!convertStringToBool("false"));
      }
    }

    TEST_CASE("test vector functions") {
      std::vector<int> intVector = { 1, 2, 3 };
      std::vector<std::string> stringVector = { "hello", "world" };
      SECTION("test contains") {
        REQUIRE(contains(intVector, 1));
        REQUIRE(!contains(intVector, 4));

        REQUIRE(contains<std::string>(stringVector, "hello"));
        REQUIRE(!contains<std::string>(stringVector, "test"));
      }

      SECTION("test remove") {
        remove(intVector, 1);
        REQUIRE(intVector.size() == 2);
        REQUIRE(!contains(intVector, 1));
        remove(intVector, 4);
        REQUIRE(intVector.size() == 2);
        REQUIRE(!contains(intVector, 4));

        remove<std::string>(stringVector, "hello");
        REQUIRE(stringVector.size() == 1);
        REQUIRE(!contains<std::string>(stringVector, "hello"));
        remove<std::string>(stringVector, "test");
        REQUIRE(stringVector.size() == 1);
        REQUIRE(!contains<std::string>(stringVector, "test"));
      }
    }
  }
}