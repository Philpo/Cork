#pragma once
#include <math.h>

class Vector3 {
public:
  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  ~Vector3() {}

  float getX() const { return x; }
  float getY() const { return y; }
  float getZ() const { return z; }

  void setX(float x) { this->x = x; }
  void setY(float y) { this->y = y; }
  void setZ(float z) { this->z = z; }

  Vector3 normalise() const;
  void clamp(float maxValue);
  float magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
  static float dotProduct(Vector3& lhs, Vector3& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z); }
  static Vector3 crossProduct(Vector3& lhs, Vector3& rhs);

  Vector3 operator+(const Vector3& rhs) const;
  Vector3 operator-(const Vector3& rhs) const;
  Vector3 operator*(float scalar) const;
  Vector3 operator/(float scalar) const;
  void operator+=(const Vector3& rhs);
  void operator-=(const Vector3 & rhs);
  void operator*=(float scalar);
  void operator/=(float scalar);
  Vector3 operator=(float scalar);
  Vector3 operator=(const Vector3& rhs);
private:
  float x, y, z;
};