#ifndef OBJECT_H
#define OBJECT_H

#include "Point3.h"
#include "Ray3.h"
#include "Color.h"

#include <utility>
#include <iostream>

// TODO: refactor rayIntersect to return color at hit point
class Object {
  public:
    Color color; // TODO: change to Material

    // returns value of parameter of ray that gives the intersection point
    virtual std::pair<bool, float_type> findIntersectParam(Ray3 ray) const = 0;

  private:
    // having a purely boolean function to check ray intersect seems natural in theory
    // but it turns out that the algebra used in calculating whether there exists an intersection
    // is also instrumental in calculating the intersect param (if it exists)
    // so I have opted to not implement such a boolean function for now
    // bool doesRayIntersect(Ray3 ray);

    Ray3 normal(Point3 hitPoint);
};

#endif /* OBJECT_H */
