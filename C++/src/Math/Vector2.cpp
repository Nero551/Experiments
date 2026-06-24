#include "Vector.h"
#include <cmath>
#include <iostream>
#include <ostream>

Vector2::Vector2(float x, float y) : X(x), Y(y) {}

Vector2 Vector2::operator+(const Vector2 &vec2) const { return {X + vec2.X, Y + vec2.Y}; }

Vector2 Vector2::operator-(const Vector2 &vec2) const { return {X - vec2.X, Y - vec2.Y}; }

Vector2 Vector2::operator*(float scalar) const { return {scalar * X, scalar * Y}; }

Vector2 Vector2::operator/(float scalar) const { return {X / scalar, Y / scalar}; }

Vector2 operator*(float scalar, const Vector2 &vec2) { return vec2 * scalar; }

Vector2 operator/(float scalar, const Vector2 &vec2) { return vec2 * (1.0f / scalar); }

Vector2 &Vector2::operator+=(const Vector2 &vec2) { return *this = *this + vec2; }
Vector2 &Vector2::operator-=(const Vector2 &vec2) { return *this = *this - vec2; }
Vector2 &Vector2::operator*=(float scalar) { return *this = *this * scalar; }
Vector2 &Vector2::operator/=(float scalar) { return *this = *this / scalar; }

std::ostream &operator<<(std::ostream &os, const Vector2 &vec2) {
  os << "(" << vec2.X << ", " << vec2.Y << ")";
  return os;
}

float Vector2::LengthSquared() const { return X * X + Y * Y; }

float Vector2::Length() const { return std::sqrt(LengthSquared()); }

Vector2 Vector2::Normalized() const {
  float length = Length();
  return {X / length, Y / length};
}

float Vector2::Dot(const Vector2 &vec2) const { return X * vec2.X + Y * vec2.Y; }

float Vector2::Distance(const Vector2 &vec2) const { return (*this - vec2).Length(); }
