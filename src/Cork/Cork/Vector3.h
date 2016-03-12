#pragma once
#include <math.h>

class Vector3 {
public:
  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  ~Vector3() {}

  inline float getX() const { return x; }
  inline float getY() const { return y; }
  inline float getZ() const { return z; }

  inline void setX(float x) { this->x = x; }
  inline void setY(float y) { this->y = y; }
  inline void setZ(float z) { this->z = z; }

  Vector3 normalise() const;
  void clamp(float maxValue);
  inline float magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
  inline static float dotProduct(Vector3& lhs, Vector3& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z); }
  inline static Vector3 crossProduct(Vector3& lhs, Vector3& rhs);

  inline Vector3 operator+(const Vector3& rhs) const;
  inline Vector3 operator-(const Vector3& rhs) const;
  inline Vector3 operator*(float scalar) const;
  inline Vector3 operator/(float scalar) const;
  inline void operator+=(const Vector3& rhs);
  inline void operator-=(const Vector3 & rhs);
  inline void operator*=(float scalar);
  inline void operator/=(float scalar);
  inline Vector3 operator=(float scalar);
  inline Vector3 operator=(const Vector3& rhs);
private:
  float x, y, z;
};

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