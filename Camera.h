#ifndef CAMERA_H
#define CAMERA_H

#include "Ray3.h"
#include "settings.h"

class Camera {
  public:
    // Ray3 cameraRay = Ray3(Point3(0., 0., 0.), Vec3(0., 0., -1.));

    // TODO: add ability to customise position, direction and orientation

    float_type focalLength = 1.;
};

#endif /* CAMERA_H */
