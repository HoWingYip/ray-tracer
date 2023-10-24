#ifndef OBJECT_H
#define OBJECT_H

#include "Point3.h"
#include "Ray3.h"

#include <utility>
class Object {
  public:
    Vec3 color;
    std::pair<bool, Point3> rayIntersect(Ray3 ray);
};

#endif /* OBJECT_H */
