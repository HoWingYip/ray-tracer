#ifndef VEC3_H
#define VEC3_H

#include "settings.h"

#include <cmath>

class Vec3 {
  public:
    Vec3() {
      e[0] = e[1] = e[2] = 0;
    }

    Vec3(float_type x, float_type y, float_type z) : e{x, y, z} {}

    inline float_type x() const { return e[0]; }
    inline float_type y() const { return e[1]; }
    inline float_type z() const { return e[2]; }

    inline float_type operator[](std::size_t i) const { return e[i]; }
    inline float_type operator[](std::size_t i) { return e[i]; }

    inline float_type lengthSquared() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline float_type length() const {
      return std::sqrt(lengthSquared());
    }

    inline Vec3 norm() const {
      return *this / length();
    }

    friend inline float_type dot(const Vec3 &u, const Vec3 &v);
    friend inline Vec3 cross(const Vec3 &u, const Vec3 &v);

    // TODO: consider modifying operator overloads according to
    // https://stackoverflow.com/questions/14482380/multiplying-an-object-with-a-constant-from-left-side

    inline Vec3 operator+=(const Vec3 &other) {
      e[0] += other.e[0];
      e[1] += other.e[1];
      e[2] += other.e[2];
      return *this;
    }
    friend inline Vec3 operator+(const Vec3 &u, const Vec3 &v);

    inline Vec3 operator-() const {
      return Vec3(-e[0], -e[1], -e[2]);
    }

    inline Vec3 operator-=(const Vec3 &other) {
      e[0] -= other.e[0];
      e[1] -= other.e[1];
      e[2] -= other.e[2];
      return *this;
    }
    friend inline Vec3 operator-(const Vec3 &u, const Vec3 &v);

    inline Vec3 operator*=(const float_type k) {
      e[0] *= k;
      e[1] *= k;
      e[2] *= k;
      return *this;
    }
    friend inline Vec3 operator*(const float_type k, const Vec3 &v);
    friend inline Vec3 operator*(const Vec3 &v, const float_type k);

    inline Vec3 operator*=(const Vec3 &other) {
      e[0] *= other.e[0];
      e[1] *= other.e[1];
      e[2] *= other.e[2];
      return *this;
    }
    friend inline Vec3 operator*(const Vec3 &u, const Vec3 &v);

    inline Vec3 operator/=(const float_type k) {
      *this *= (1/k);
      return *this;
    }
    friend inline Vec3 operator/(const Vec3 &v, const float_type k);
  
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

#endif /* VEC3_H */
