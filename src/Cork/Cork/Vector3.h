#pragma once

template <class T>
class Vector3 {
public:
  Vector3() : x(0), y(0), z(0) {}
  Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
  ~Vector3() {}

  inline T getX() const { return x; }
  inline T getY() const { return y; }
  inline T getZ() const { return z; }

  inline void setX(T x) { this->x = x; }
  inline void setY(T y) { this->y = y; }
  inline void setZ(T z) { this->z = z; }

  Vector3<T> normalise() const;
  void clamp(T maxValue);
  inline T magnitude() const { return sqrt(pow(x, 2) + pow(y, 2)); }
  inline static T dotProduct(Vector3<T>& lhs, Vector3<T>& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z); }

  inline Vector3<T> operator+(const Vector3<T>& rhs) const;
  inline Vector3<T> operator-(const Vector3<T>& rhs) const;
  inline Vector3<T> operator*(T scalar) const;
  inline Vector3<T> operator/(T scalar) const;
  inline void operator+=(const Vector3<T>& rhs);
  inline void operator-=(const Vector3<T> & rhs);
  inline void operator*=(T scalar);
  inline void operator/=(T scalar);
  inline Vector3<T> operator=(T scalar);
  inline Vector3<T> operator=(const Vector3<T>& rhs);
private:
  T x, y, z;
};

template <class T>
Vector3<T> Vector3<T>::normalise() const {
  float magnitude = magnitude();
  if (magnitude == 0) {
    return *this;
  }
  else {
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
  }
}

template <class T>
void Vector3<T>::clamp(T maxValue) {
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

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const {
  return Vector3<T>(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const {
  return Vector3<T>(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

template <class T>
Vector3<T> Vector3<T>::operator*(T scalar) const {
  return Vector3<T>(x * scalar, y * scalar, z * scalar);
}

template <class T>
Vector3<T> Vector3<T>::operator/(T scalar) const {
  return Vector3<T>(x / scalar, y / scalar, z / scalar);
}

template <class T>
void Vector3<T>::operator+=(const Vector3<T>& rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
}

template <class T>
void Vector3<T>::operator-=(const Vector3<T>& rhs) {
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
}

template <class T>
void Vector3<T>::operator*=(T scalar) {
  this->x *= rhs.x;
  this->y *= rhs.y;
  this->z *= rhs.z;
}

template <class T>
void Vector3<T>::operator/=(T scalar) {
  this->x /= rhs.x;
  this->y /= rhs.y;
  this->z /= rhs.z;
}

template <class T>
Vector3<T> Vector3<T>::operator=(T scalar) {
  x = scalar;
  y = scalar;
  z = scalar;
  return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator=(const Vector3<T>& rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}