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

Vector3 Vector3::crossProduct(Vector3& lhs, Vector3& rhs) {
  return Vector3((lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z), (lhs.x * rhs.y) - (lhs.y * rhs.x));
}

Vector3 Vector3::operator+(const Vector3& rhs) const {
  return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs) const {
  return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

Vector3 Vector3::operator*(float scalar) const {
  return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const {
  return scalar == 0 ? *this : Vector3(x / scalar, y / scalar, z / scalar);
}

void Vector3::operator+=(const Vector3& rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
}

void Vector3::operator-=(const Vector3& rhs) {
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
}

void Vector3::operator*=(float scalar) {
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
}

void Vector3::operator/=(float scalar) {
  if (scalar == 0) {
    return;
  }

  this->x /= scalar;
  this->y /= scalar;
  this->z /= scalar;
}

Vector3 Vector3::operator=(float scalar) {
  x = scalar;
  y = scalar;
  z = scalar;
  return *this;
}

Vector3 Vector3::operator=(const Vector3& rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}