#ifndef OBJECT_H
#define OBJECT_H

#include "Point3.h"
#include "Ray3.h"

#include <utility>
#include <iostream>

// TODO: refactor rayIntersect to return color at hit point
class Object {
  public:
    Color color; // TODO: change to Material

    // returns value of parameter of ray that gives the intersection point
    virtual std::tuple<bool, Point3, float_type> findIntersectParam(Ray3 ray) const = 0;
    virtual Ray3 normal(Point3 hitPoint) const = 0;    
};

#endif /* OBJECT_H */
