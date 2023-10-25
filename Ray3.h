#ifndef RAY3_H
#define RAY3_H

#include "Vec3.h"
#include "Point3.h"
#include "settings.h"

class Ray3 {
  public:
    Point3 base;
    Vec3 direction;

    Ray3() : base(Point3()), direction(Vec3()) {}
    Ray3(Point3 a_, Vec3 d_) : base(a_), direction(d_) {}

    Point3 produce(const float_type t) {
      return base + t*direction;
    }
};

#endif /* RAY3_H */
