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

Vector3 Vector3::rotateX(float angle) {
  angle = angle * M_PI / 180.0f;
  Vector3 toReturn;
  Vector3 topRow(1.0f, 0.0f, 0.0f);
  Vector3 middleRow(0.0f, cos(angle), sin(angle));
  Vector3 bottomRow(0.0f, -sin(angle), cos(angle));

  float newX = (topRow.x * x) + (topRow.y * y) + (topRow.z * z);
  float newY = (middleRow.x * x) + (middleRow.y * y) + (middleRow.z * z);
  float newZ = (bottomRow.x * x) + (bottomRow.y * y) + (bottomRow.z * z);

  toReturn.x = newX;
  toReturn.y = newY;
  toReturn.z = newZ;
  
  return toReturn;
}

Vector3 Vector3::rotateY(float angle) {
  angle = angle * M_PI / 180.0f;
  Vector3 toReturn;
  Vector3 topRow(cos(angle), 0.0f, -sin(angle));
  Vector3 middleRow(0.0f, 1.0f, 0.0f);
  Vector3 bottomRow(sin(angle), 0.0f, cos(angle));

  float newX = (topRow.x * x) + (topRow.y * y) + (topRow.z * z);
  float newY = (middleRow.x * x) + (middleRow.y * y) + (middleRow.z * z);
  float newZ = (bottomRow.x * x) + (bottomRow.y * y) + (bottomRow.z * z);

  toReturn.x = newX;
  toReturn.y = newY;
  toReturn.z = newZ;

  return toReturn;
}

Vector3 Vector3::rotateZ(float angle) {
  angle = angle * M_PI / 180.0f;
  Vector3 toReturn;
  Vector3 topRow(cos(angle), sin(angle), 0.0f);
  Vector3 middleRow(-sin(angle), cos(angle), 0.0f);
  Vector3 bottomRow(0.0f, 0.0f, 1.0f);

  float newX = (topRow.x * x) + (topRow.y * y) + (topRow.z * z);
  float newY = (middleRow.x * x) + (middleRow.y * y) + (middleRow.z * z);
  float newZ = (bottomRow.x * x) + (bottomRow.y * y) + (bottomRow.z * z);

  toReturn.x = newX;
  toReturn.y = newY;
  toReturn.z = newZ;

  return toReturn;
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