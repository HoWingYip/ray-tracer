#ifndef UTILITY_H
#define UTILITY_H

#include "Vec3.h"

#include <random>

float_type randomFloat(float_type min, float_type max) {
  return min + (max-min) * (float_type)rand() / RAND_MAX;
}

// Vec3 randomInUnitSphere() {
//   return Vec3()
// }

#endif /* UTILITY_H */
