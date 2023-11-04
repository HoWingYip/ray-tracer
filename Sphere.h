#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "settings.h"

#include <algorithm>

class Sphere : public Object {
  using Object::findIntersectParam;

  public:
    Point3 center;
    float_type radius;

    Sphere(Point3 c_, float_type r_, Color color_) : center(c_), radius(r_) {
      color = color_;
    }

    // returns value of parameter of ray that gives the intersection point
    std::tuple<bool, Point3, float_type> findIntersectParam(Ray3 ray) const override {
      float_type A = ray.direction.length();
      float_type B = 2*dot(ray.direction, (ray.base - center));
      float_type C = (ray.base - center).lengthSquared() - radius*radius;

      float_type discriminant = B*B - 4*A*C;

      if (discriminant < 0) {
        return {false, Point3(), 0};
      }

      float_type t1 = (sqrt(discriminant) - B) / (2*A);

      if (discriminant == 0) {
        return {true, ray.produce(t1), t1};
      }

      float_type t2 = (-sqrt(discriminant) - B) / (2*A);
      
      if (t1 < EPSILON && t2 < EPSILON) {
        // intersection point is in opposite direction of ray direction vector
        return {false, Point3(), 0};
      } else {
        // at least one of t1 and t2 is non-negative
        float_type t = std::min(std::max(0., t1), std::max(0., t2));
        return {true, ray.produce(t), t};
      }
    }

    Ray3 normal(Point3 hitPoint) const override {
      return Ray3(hitPoint, (hitPoint - center).norm());
    }

  private:
    
};

#endif /* SPHERE_H */
