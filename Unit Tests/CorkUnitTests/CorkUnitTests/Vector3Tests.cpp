#include "stdafx.h"
#include "catch.hpp"
#include "Vector3.h"
#include "TypeDefs.h"
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorkUnitTests {
  namespace vector3 {
    TEST_CASE("test vector3 constructors") {
      SECTION("test default constuctor") {
        Vector3 v;
        REQUIRE(v.getX() == approx(0));
        REQUIRE(v.getY() == approx(0));
        REQUIRE(v.getZ() == approx(0));
      }
      SECTION("test parameterised constructor") {
        Vector3 v(1.0f, 1.0f, 1.0f);
        REQUIRE(v.getX() == approx(1.0f));
        REQUIRE(v.getY() == approx(1.0f));
        REQUIRE(v.getZ() == approx(1.0f));
      }
    }

    TEST_CASE("test setting x") {
      Vector3 v;

      SECTION("test setting x with a positive value") {
        v.setX(1.0f);
        REQUIRE(v.getX() == approx(1.0f));
      }
      SECTION("test setting x with a negative value") {
        v.setX(-1.0f);
        REQUIRE(v.getX() == approx(-1.0f));
      }
      SECTION("test setting x with a zero") {
        v.setX(0.0f);
        REQUIRE(v.getX() == approx(0.0f));
      }
      SECTION("test setting x with max float value") {
        v.setX(std::numeric_limits<float>::max());
        REQUIRE(v.getX() == approx(std::numeric_limits<float>::max()));
      }
      SECTION("test setting x with min float value") {
        v.setX(std::numeric_limits<float>::min());
        REQUIRE(v.getX() == approx(std::numeric_limits<float>::min()));
      }
    }

    TEST_CASE("test setting y") {
      Vector3 v;

      SECTION("test setting y with a positive value") {
        v.setY(1.0f);
        REQUIRE(v.getY() == approx(1.0f));
      }
      SECTION("test setting y with a negative value") {
        v.setY(-1.0f);
        REQUIRE(v.getY() == approx(-1.0f));
      }
      SECTION("test setting y with a zero") {
        v.setY(0.0f);
        REQUIRE(v.getY() == approx(0.0f));
      }
      SECTION("test setting y with may float value") {
        v.setY(std::numeric_limits<float>::max());
        REQUIRE(v.getY() == approx(std::numeric_limits<float>::max()));
      }
      SECTION("test setting y with min float value") {
        v.setY(std::numeric_limits<float>::min());
        REQUIRE(v.getY() == approx(std::numeric_limits<float>::min()));
      }
    }

    TEST_CASE("test setting z") {
      Vector3 v;

      SECTION("test setting z with a positive value") {
        v.setZ(1.0f);
        REQUIRE(v.getZ() == approx(1.0f));
      }
      SECTION("test setting z with a negative value") {
        v.setZ(-1.0f);
        REQUIRE(v.getZ() == approx(-1.0f));
      }
      SECTION("test setting z with a zero") {
        v.setZ(0.0f);
        REQUIRE(v.getZ() == approx(0.0f));
      }
      SECTION("test setting z with maz float value") {
        v.setZ(std::numeric_limits<float>::max());
        REQUIRE(v.getZ() == approx(std::numeric_limits<float>::max()));
      }
      SECTION("test setting z with min float value") {
        v.setZ(std::numeric_limits<float>::min());
        REQUIRE(v.getZ() == approx(std::numeric_limits<float>::min()));
      }
    }

    TEST_CASE("test magnitude") {
      SECTION("test magnitude with positive values") {
        Vector3 v(3.0f, 3.0f, 3.0f);
        REQUIRE(v.magnitude() == approx(5.196));
      }
      SECTION("test magnitude with negative values") {
        Vector3 v(-3.0f, -3.0f, -3.0f);
        REQUIRE(v.magnitude() == approx(5.196));
      }
      SECTION("test magnitude with zero values") {
        Vector3 v(0.0f, 0.0f, 0.0f);
        REQUIRE(v.magnitude() == approx(0.0f));
      }
    }

    TEST_CASE("test normalise") {
      SECTION("test normalise with positive values") {
        Vector3 v(3.0f, 3.0f, 3.0f);
        Vector3 result = v.normalise();
        REQUIRE(result.getX() == approx(0.57735));
        REQUIRE(result.getY() == approx(0.57735));
        REQUIRE(result.getZ() == approx(0.57735));
      }
      SECTION("test normalise with negative values") {
        Vector3 v(-3.0f, -3.0f, -3.0f);
        Vector3 result = v.normalise();
        REQUIRE(result.getX() == approx(-0.57735));
        REQUIRE(result.getY() == approx(-0.57735));
        REQUIRE(result.getZ() == approx(-0.57735));
      }
      SECTION("test normalise with zero values") {
        Vector3 v(0.0f, 0.0f, 0.0f);
        Vector3 result = v.normalise();
        REQUIRE(result.getX() == approx(v.getX()));
        REQUIRE(result.getY() == approx(v.getY()));
        REQUIRE(result.getZ() == approx(v.getZ()));
      }
      SECTION("test normalise of unit vector") {
        Vector3 v(1.0f, 0.0f, 0.0f);
        Vector3 result = v.normalise();
        REQUIRE(result.getX() == approx(v.getX()));
        REQUIRE(result.getY() == approx(v.getY()));
        REQUIRE(result.getZ() == approx(v.getZ()));
      }
    }

    TEST_CASE("test clamp") {
      SECTION("test positive clamp with positive values") {
        Vector3 v(3.0f, 3.0f, 3.0f);
        v.clamp(1.0f);
        REQUIRE(v.getX() == approx(1.0f));
        REQUIRE(v.getY() == approx(1.0f));
        REQUIRE(v.getZ() == approx(1.0f));
      }
      SECTION("test positive clamp with negative values") {
        Vector3 v(-3.0f, -3.0f, -3.0f);
        v.clamp(1.0f);
        REQUIRE(v.getX() == approx(-1.0f));
        REQUIRE(v.getY() == approx(-1.0f));
        REQUIRE(v.getZ() == approx(-1.0f));
      }
      SECTION("test negative clamp with positive values") {
        Vector3 v(3.0f, 3.0f, 3.0f);
        v.clamp(-1.0f);
        REQUIRE(v.getX() == approx(1.0f));
        REQUIRE(v.getY() == approx(1.0f));
        REQUIRE(v.getZ() == approx(1.0f));
      }
      SECTION("test negative clamp with negative values") {
        Vector3 v(-3.0f, -3.0f, -3.0f);
        v.clamp(-1.0f);
        REQUIRE(v.getX() == approx(-1.0f));
        REQUIRE(v.getY() == approx(-1.0f));
        REQUIRE(v.getZ() == approx(-1.0f));
      }
      SECTION("test partial clamp") {
        Vector3 v(3.0f, 0.5f, 0.01f);
        v.clamp(1.0f);
        REQUIRE(v.getX() == approx(1.0f));
        REQUIRE(v.getY() == approx(0.5f));
        REQUIRE(v.getZ() == approx(0.01f));
      }
    }

    TEST_CASE("test operators") {
      SECTION("test assignment") {
        SECTION("test assignment to scalar") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = 2.0f;
          REQUIRE(v.getX() == approx(2.0f));
          REQUIRE(v.getY() == approx(2.0f));
          REQUIRE(v.getZ() == approx(2.0f));
        }
        SECTION("test assignment to vector") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = Vector3(1.5f, 2.0f, 3.0f);
          REQUIRE(v.getX() == approx(1.5f));
          REQUIRE(v.getY() == approx(2.0f));
          REQUIRE(v.getZ() == approx(3.0f));
        }
      }

      SECTION("test addition") {
        SECTION("test positive addition") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v + Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(2.5f));
          REQUIRE(v.getY() == approx(2.7f));
          REQUIRE(v.getZ() == approx(2.9f));
        }
        SECTION("test positive addition with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v = v + Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(0.5f));
          REQUIRE(v.getY() == approx(0.7f));
          REQUIRE(v.getZ() == approx(0.9f));
        }
        SECTION("test negative addition") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v + Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(-0.5f));
          REQUIRE(v.getY() == approx(-0.7f));
          REQUIRE(v.getZ() == approx(-0.9f));
        }
        SECTION("test negative addition with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v = v + Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(-2.5f));
          REQUIRE(v.getY() == approx(-2.7f));
          REQUIRE(v.getZ() == approx(-2.9f));
        }
        SECTION("test zero addition") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v + Vector3(0.0f, 0.0f, 0.0f);
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.0f));
          REQUIRE(v.getZ() == approx(1.0f));
        }
        SECTION("test += positive") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v += Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(2.5f));
          REQUIRE(v.getY() == approx(2.7f));
          REQUIRE(v.getZ() == approx(2.9f));
        }
        SECTION("test += positive with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v += Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(0.5f));
          REQUIRE(v.getY() == approx(0.7f));
          REQUIRE(v.getZ() == approx(0.9f));
        }
        SECTION("test += negative") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v += Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(-0.5f));
          REQUIRE(v.getY() == approx(-0.7f));
          REQUIRE(v.getZ() == approx(-0.9f));
        }
        SECTION("test += negative with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v += Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(-2.5f));
          REQUIRE(v.getY() == approx(-2.7f));
          REQUIRE(v.getZ() == approx(-2.9f));
        }
        SECTION("test += zero") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v += Vector3(0.0f, 0.0f, 0.0f);
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.0f));
          REQUIRE(v.getZ() == approx(1.0f));
        }
      }

      SECTION("test subtraction") {
        SECTION("test positive subtraction") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v - Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(-0.5f));
          REQUIRE(v.getY() == approx(-0.7f));
          REQUIRE(v.getZ() == approx(-0.9f));
        }
        SECTION("test positive subtraction with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v = v - Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(-2.5f));
          REQUIRE(v.getY() == approx(-2.7f));
          REQUIRE(v.getZ() == approx(-2.9f));
        }
        SECTION("test negative subtraction") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v - Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(2.5f));
          REQUIRE(v.getY() == approx(2.7f));
          REQUIRE(v.getZ() == approx(2.9f));
        }
        SECTION("test negative subtraction with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v = v - Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(0.5f));
          REQUIRE(v.getY() == approx(0.7f));
          REQUIRE(v.getZ() == approx(0.9f));
        }
        SECTION("test zero subtraction") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v = v - Vector3(0.0f, 0.0f, 0.0f);
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.0f));
          REQUIRE(v.getZ() == approx(1.0f));
        }
        SECTION("test -= positive") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v -= Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(-0.5f));
          REQUIRE(v.getY() == approx(-0.7f));
          REQUIRE(v.getZ() == approx(-0.9f));
        }
        SECTION("test -= positive with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v -= Vector3(1.5f, 1.7f, 1.9f);
          REQUIRE(v.getX() == approx(-2.5f));
          REQUIRE(v.getY() == approx(-2.7f));
          REQUIRE(v.getZ() == approx(-2.9f));
        }
        SECTION("test -= negative") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v -= Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(2.5f));
          REQUIRE(v.getY() == approx(2.7f));
          REQUIRE(v.getZ() == approx(2.9f));
        }
        SECTION("test -= negative with negative values") {
          Vector3 v(-1.0f, -1.0f, -1.0f);
          v -= Vector3(-1.5f, -1.7f, -1.9f);
          REQUIRE(v.getX() == approx(0.5f));
          REQUIRE(v.getY() == approx(0.7f));
          REQUIRE(v.getZ() == approx(0.9f));
        }
        SECTION("test -= zero") {
          Vector3 v(1.0f, 1.0f, 1.0f);
          v -= Vector3(0.0f, 0.0f, 0.0f);
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.0f));
          REQUIRE(v.getZ() == approx(1.0f));
        }
      }

      SECTION("test multiplication") {
        SECTION("test positive multiplication") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v * 2.0f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test positive multiplication with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v * 2.0f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test positive fractional multiplication") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v * 0.5f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test positive fractional multiplication with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v * 0.5f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test negative multiplication") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v * -2.0f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test negative multiplication negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v * -2.0f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test negative fractional multiplication") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v * -0.5f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test negative fractional multiplication with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v * -0.5f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test zero multiplication") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v * 0.0f;
          REQUIRE(v.getX() == approx(0.0f));
          REQUIRE(v.getY() == approx(0.0f));
          REQUIRE(v.getZ() == approx(0.0f));
        }
        SECTION("test *= positive") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v *= 2.0f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test *= positive with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v *= 2.0f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test *= positive fractional") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v *= 0.5f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test *= positive fractional with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v *= 0.5f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test *= negative") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v *= -2.0f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test *= negative with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v *= -2.0f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test *= negative fractional") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v *= -0.5f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test *= negative fractional with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v *= -0.5f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test *= zero") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v *= 0.0f;
          REQUIRE(v.getX() == approx(0.0f));
          REQUIRE(v.getY() == approx(0.0f));
          REQUIRE(v.getZ() == approx(0.0f));
        }
      }

      SECTION("test division") {
        SECTION("test positive division") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v / 2.0f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test positive division with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v / 2.0f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test positive fractional division") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v / 0.5f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test positive fractional division with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v / 0.5f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test negative division") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v / -2.0f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test negative division with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v / -2.0f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test negative fractional division") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v / -0.5f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test negative fractional division with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v = v / -0.5f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test zero division") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v = v / 0.0f;
          REQUIRE(v.getX() == approx(2.0f));
          REQUIRE(v.getY() == approx(2.5f));
          REQUIRE(v.getZ() == approx(3.0f));
        }
        SECTION("test /= positive") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v /= 2.0f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test /= positive with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v /= 2.0f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test /= positive fractional") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v /= 0.5f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test /= positive fractional with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v /= 0.5f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test /= negative") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v /= -2.0f;
          REQUIRE(v.getX() == approx(-1.0f));
          REQUIRE(v.getY() == approx(-1.25f));
          REQUIRE(v.getZ() == approx(-1.5f));
        }
        SECTION("test /= negative with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v /= -2.0f;
          REQUIRE(v.getX() == approx(1.0f));
          REQUIRE(v.getY() == approx(1.25f));
          REQUIRE(v.getZ() == approx(1.5f));
        }
        SECTION("test /= negative fractional") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v /= -0.5f;
          REQUIRE(v.getX() == approx(-4.0f));
          REQUIRE(v.getY() == approx(-5.0f));
          REQUIRE(v.getZ() == approx(-6.0f));
        }
        SECTION("test /= negative fractional with negative values") {
          Vector3 v(-2.0f, -2.5f, -3.0f);
          v /= -0.5f;
          REQUIRE(v.getX() == approx(4.0f));
          REQUIRE(v.getY() == approx(5.0f));
          REQUIRE(v.getZ() == approx(6.0f));
        }
        SECTION("test /= zero") {
          Vector3 v(2.0f, 2.5f, 3.0f);
          v /= 0.0f;
          REQUIRE(v.getX() == approx(2.0f));
          REQUIRE(v.getY() == approx(2.5f));
          REQUIRE(v.getZ() == approx(3.0f));
        }
      }
    }

    TEST_CASE("test dot product") {
      SECTION("test dot product with positive vectors") {
        float result = Vector3::dotProduct(Vector3(1.0f, 2.0f, 3.0f), Vector3(2.0f, 3.0f, 4.0f));
        REQUIRE(result == approx(20.0f));
      }
      SECTION("test dot product with negative vectors") {
        float result = Vector3::dotProduct(Vector3(-1.0f, -2.0f, -3.0f), Vector3(-2.0f, -3.0f, -4.0f));
        REQUIRE(result == approx(20.0f));
      }
      SECTION("test dot product with one positive & one negative vector") {
        float result = Vector3::dotProduct(Vector3(1.0f, 2.0f, 3.0f), Vector3(-2.0f, -3.0f, -4.0f));
        REQUIRE(result == approx(-20.0f));
      }
      SECTION("test dot product with fractional positive vectors") {
        float result = Vector3::dotProduct(Vector3(1.5f, 2.25f, 3.75f), Vector3(2.0f, 3.0f, 4.0f));
        REQUIRE(result == approx(24.75f));
      }
      SECTION("test dot product with fractional negative vectors") {
        float result = Vector3::dotProduct(Vector3(-1.5f, -2.25f, -3.75f), Vector3(-2.0f, -3.0f, -4.0f));
        REQUIRE(result == approx(24.75f));
      }
      SECTION("test dot product with fractional vectors, one positive & one negative") {
        float result = Vector3::dotProduct(Vector3(1.5f, 2.25f, 3.75f), Vector3(-2.0f, -3.0f, -4.0f));
        REQUIRE(result == approx(-24.75f));
      }
    }

    TEST_CASE("test cross product") {
      SECTION("test cross product with positive vectors") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, 2.0f), Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(result.getX() == approx(-2.0f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
      SECTION("test dot product with negative vectors") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, -2.0f), Vector3(0.0f, -1.0f, 0.0f));
        REQUIRE(result.getX() == approx(-2.0f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
      SECTION("test dot product with one positive & one negative vector") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, -2.0f), Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(result.getX() == approx(2.0f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
      SECTION("test dot product with fractional positive vectors") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, 2.5f), Vector3(0.0f, 1.5f, 0.0f));
        REQUIRE(result.getX() == approx(-3.75f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
      SECTION("test dot product with fractional negative vectors") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, -2.5f), Vector3(0.0f, -1.5f, 0.0f));
        REQUIRE(result.getX() == approx(-3.75f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
      SECTION("test dot product with fractional vectors, one positive & one negative") {
        Vector3 result = Vector3::crossProduct(Vector3(0.0f, 0.0f, -2.5f), Vector3(0.0f, 1.5f, 0.0f));
        REQUIRE(result.getX() == approx(3.75f));
        REQUIRE(result.getY() == approx(0.0f));
        REQUIRE(result.getZ() == approx(0.0f));
      }
    }
  }
}