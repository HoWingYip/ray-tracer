#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Point3.h"
#include "Color.h"
#include "settings.h"

#include <algorithm>

class Sphere : Object {
  public:
    Point3 center;
    float_type radius;

    Sphere(Point3 c_, float_type r_, Color color_) : center(c_), radius(r_) {
      color = color_;
    }

    // returns value of parameter of ray that gives the intersection point
    std::pair<bool, float_type> findIntersectParam(Ray3 ray) {
      float_type A = ray.direction.length();
      float_type B = 2*dot(ray.direction, (ray.base - center));
      float_type C = (ray.base - center).lengthSquared() - radius*radius;

      float_type discriminant = B*B - 4*A*C;

      if (discriminant < 0) {
        return {false, 0};
      }

      float_type t1 = (sqrt(discriminant) - B) / (2*A);

      if (discriminant == 0) {
        return {true, t1};
      }

      float_type t2 = (-sqrt(discriminant) - B) / (2*A);
      
      if (t1 < 0 && t2 < 0) {
        // intersection point is in opposite direction of ray direction vector
        return {false, 0};
      } else {
        // at least one of t1 and t2 is non-negative
        return {true, std::min(std::max(0., t1), std::max(0., t2))};
      }
    }

  private:
    Ray3 normal(Point3 hitPoint) {
      return Ray3(hitPoint, (hitPoint - center).norm());
    }
};

#endif /* SPHERE_H */
