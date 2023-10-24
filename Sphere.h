#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Point3.h"
#include "settings.h"

#include <algorithm>

class Sphere : Object {
  Point3 center;
  float_type radius;

  Sphere(Point3 c_, float_type r_, Vec3 color_) : center(c_), radius(r_) {
    color = color_;
  }

  std::pair<bool, Point3> rayIntersect(Ray3 ray) {
    float_type A = ray.direction.length();
    float_type B = 2*dot(ray.direction, (ray.base - center));
    float_type C = (ray.base - center).lengthSquared() - radius*radius;

    float_type discriminant = B*B - 4*A*C;

    if (discriminant < 0) {
      return {false, Point3()};
    }

    float_type t1 = (sqrt(discriminant) - B) / (2*A);

    if (discriminant == 0) {
      return {true, ray.produce(t1)};
    }

    float_type t2 = (-sqrt(discriminant) - B) / (2*A);
    
    if (t1 < 0 && t2 < 0) {
      // intersection point is in opposite direction of ray direction vector
      return {false, Point3()};
    } else {
      // at least one of t1 and t2 is non-negative
      return {true, ray.produce(std::min(std::max(0., t1), std::max(0., t2)))};
    }
  }

  Ray3 normal(Point3 hitPoint) {
    return Ray3(hitPoint, (hitPoint - center).norm());
  }
};

#endif /* SPHERE_H */
