#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Point3.h"
#include "settings.h"

class Sphere : Object {
  Point3 center;
  float_type radius;

  Sphere(Point3 c_, float_type r_) : center(c_), radius(r_) {}

  std::pair<bool, Point3> rayIntersect(Ray3 ray) {
    
  }

  Ray3 normal(Point3 hitPoint) {
    return Ray3(hitPoint, (hitPoint - center).norm());
  }
};

#endif /* SPHERE_H */
