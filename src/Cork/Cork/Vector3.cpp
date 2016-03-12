#include "Vector3.h"

Vector3 Vector3::normalise() const {
  float m = magnitude();
  if (m == 0 || m == 1) {
    return *this;
  }
  else {
    return Vector3(x / m, y / m, z / m);
  }
}

void Vector3::clamp(float maxValue) {
  maxValue = abs(maxValue);

  if (abs(x) > maxValue) {
    if (x < 0) {
      x = maxValue * -1;
    }
    else {
      x = maxValue;
    }
  }
  if (abs(y) > maxValue) {
    if (y < 0) {
      y = maxValue * -1;
    }
    else {
      y = maxValue;
    }
  }
  if (abs(z) > maxValue) {
    if (z < 0) {
      z = maxValue * -1;
    }
    else {
      z = maxValue;
    }
  }
}