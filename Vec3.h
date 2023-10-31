#ifndef VEC3_H
#define VEC3_H

#include "settings.h"

#include <cmath>
#include <ostream>

class Vec3 {
  public:
    Vec3() {
      e[0] = e[1] = e[2] = 0;
    }

    Vec3(float_type x, float_type y, float_type z) : e{x, y, z} {}

    float_type x() const { return e[0]; }
    void setX(float_type newX) { e[0] = newX; }

    float_type y() const { return e[1]; }
    void setY(float_type newY) { e[0] = newY; }

    float_type z() const { return e[2]; }
    void setZ(float_type newZ) { e[0] = newZ; }

    float_type operator[](std::size_t i) const { return e[i]; }
    float_type operator[](std::size_t i) { return e[i]; }

    float_type lengthSquared() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    float_type length() const {
      return std::sqrt(lengthSquared());
    }

    Vec3 norm() const {
      return *this / length();
    }

    friend float_type dot(const Vec3 &u, const Vec3 &v);
    friend Vec3 cross(const Vec3 &u, const Vec3 &v);

    // TODO: consider modifying operator overloads according to
    // https://stackoverflow.com/questions/14482380/multiplying-an-object-with-a-constant-from-left-side

    Vec3 operator+=(const Vec3 &other) {
      e[0] += other.e[0];
      e[1] += other.e[1];
      e[2] += other.e[2];
      return *this;
    }
    friend Vec3 operator+(const Vec3 &u, const Vec3 &v);

    Vec3 operator-() const {
      return Vec3(-e[0], -e[1], -e[2]);
    }

    Vec3 operator-=(const Vec3 &other) {
      e[0] -= other.e[0];
      e[1] -= other.e[1];
      e[2] -= other.e[2];
      return *this;
    }
    friend Vec3 operator-(const Vec3 &u, const Vec3 &v);

    Vec3 operator*=(const float_type k) {
      e[0] *= k;
      e[1] *= k;
      e[2] *= k;
      return *this;
    }
    friend Vec3 operator*(const float_type k, const Vec3 &v);
    friend Vec3 operator*(const Vec3 &v, const float_type k);

    Vec3 operator*=(const Vec3 &other) {
      e[0] *= other.e[0];
      e[1] *= other.e[1];
      e[2] *= other.e[2];
      return *this;
    }
    friend Vec3 operator*(const Vec3 &u, const Vec3 &v);

    Vec3 operator/=(const float_type k) {
      *this *= (1/k);
      return *this;
    }
    friend Vec3 operator/(const Vec3 &v, const float_type k);
  
  private:
    float_type e[3];
};

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return u + (-v);
}

inline Vec3 operator*(const float_type k, const Vec3 &v) {
  return Vec3(k*v.e[0], k*v.e[1], k*v.e[2]);
}
inline Vec3 operator*(const Vec3 &v, const float_type k) {
  return k*v;
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline Vec3 operator/(const Vec3 &v, const float_type k) {
  return v * (1/k);
}

inline float_type dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(
    u.e[1]*v.e[2] - u.e[2]*v.e[1],
    u.e[2]*v.e[0] - u.e[0]*v.e[2],
    u.e[0]*v.e[1] - u.e[1]*v.e[0]
  );
}

std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
  os << v.x() << ' ' << v.y() << ' ' << v.z();
  return os;
}

#endif /* VEC3_H */
