#ifndef VEC3_H
#define VEC3_H

#include "settings.h"

#include <cmath>

class Vec3 {
  public:
    Vec3() {
      v[0] = v[1] = v[2] = 0;
    }

    Vec3(float_type x, float_type y, float_type z) : v{x, y, z} {}

    inline float_type x() const { return v[0]; }
    inline float_type y() const { return v[1]; }
    inline float_type z() const { return v[2]; }

    inline float_type operator[](std::size_t i) const { return v[i]; }
    inline float_type &operator[](std::size_t i) { return v[i]; }

    inline float_type lengthSquared() const {
      return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }

    inline float_type length() const {
      return std::sqrt(lengthSquared());
    }

    inline Vec3 norm() const {
      return *this / length();
    }

    inline Vec3 operator+=(const Vec3 &other) {
      v[0] += other.v[0];
      v[1] += other.v[1];
      v[2] += other.v[2];
      return *this;
    }
    inline Vec3 Vec3::operator+(const Vec3 &other);

    inline Vec3 operator-() const {
      return Vec3(-v[0], -v[1], -v[2]);
    }

    inline Vec3 operator-(const Vec3 &other) const {
      return *this + (-other); // FIXME: operator not matched?
    }
    inline Vec3 operator-=(const Vec3 &other) {
      *this += -other;
      return *this;
    }

    inline Vec3 operator*(const float_type k) const {
      return Vec3(k*v[0], k*v[1], k*v[2]);
    }
    inline Vec3 operator*=(const float_type k) {
      v[0] *= k;
      v[1] *= k;
      v[2] *= k;
      return *this;
    }

    inline Vec3 operator*(const Vec3 &other) const {
      return Vec3(v[0]*other[0], v[1]*other[1], v[2]*other[2]);
    }
    inline Vec3 operator*=(const Vec3 &other) {
      v[0] *= other.v[0];
      v[1] *= other.v[1];
      v[2] *= other.v[2];
      return *this;
    }

    inline Vec3 operator/(const float_type k) const {
      return *this * (1/k);
    }
    inline Vec3 operator/=(const float_type k) {
      *this *= (1/k);
      return *this;
    }
  
  private:
    float_type v[3];
};

inline Vec3 Vec3::operator+(const Vec3 &other) {
  return Vec3(v[0]+other.v[0], v[1]+other.v[1], v[2]+other.v[2]);
}

#endif /* VEC3_H */
