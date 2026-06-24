#include "Vector.h"

Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

Vector3 Vector3::operator+(const Vector3 &vec3) const { return {X + vec3.X, Y + vec3.Y, Z + vec3.Z}; }

Vector3 Vector3::operator-(const Vector3 &vec3) const { return {X - vec3.X, Y - vec3.Y, Z - vec3.Z}; }

Vector3 Vector3::operator*(float scalar) const { return {scalar * X, scalar * Y, scalar * Z}; }

Vector3 Vector3::operator/(float scalar) const { return {X / scalar, Y / scalar, Z / scalar}; }

Vector3 operator*(float scalar, const Vector3 &vec3) { return vec3 * scalar; }
Vector3 operator/(float scalar, const Vector3 &vec3) { return vec3 * (1.0f / scalar); }

Vector3 &Vector3::operator+=(const Vector3 &vec3) { return *this = *this + vec3; }
Vector3 &Vector3::operator-=(const Vector3 &vec3) { return *this = *this - vec3; }
Vector3 &Vector3::operator*=(float scalar) { return *this = *this * scalar; }
Vector3 &Vector3::operator/=(float scalar) { return *this = *this / scalar; }

std::ostream &operator<<(std::ostream &os, const Vector3 &vec3) {
  os << "(" << vec3.X << ", " << vec3.Y << ", " << vec3.Z << ")";
  return os;
}

float Vector3::LengthSquared() const { return X * X + Y * Y + Z * Z; }

float Vector3::Length() const { return Vector3::LengthSquared(); };

Vector3 Vector3::Normalized() const {
  float length = Length();
  return {X / length, Y / length, Z / length};
}

float Vector3::Dot(const Vector3 &vec3) const { return X * vec3.X + Y * vec3.Y + Z * vec3.Z; }

float Vector3::Distance(const Vector3 &vec3) const { return (*this - vec3).Length(); }

Vector3 const Vector3::Zero = Vector3(0, 0, 0);
Vector3 const Vector3::Up = Vector3(0, 1, 0);
Vector3 const Vector3::One = Vector3(1, 1, 1);
Vector3 const Vector3::Forward = Vector3(0, 0, 1);
