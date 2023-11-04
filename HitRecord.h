#ifndef HITRECORD_H
#define HITRECORD_H

#include "Object.h"
#include "Vec3.h"

#include <memory>

class HitRecord {
  public:
    std::shared_ptr<Object> intersectObjPtr = nullptr;
    Point3 intersectPoint;
    Ray3 ray;
    float_type rayParam;
};

#endif /* HITRECORD_H */
