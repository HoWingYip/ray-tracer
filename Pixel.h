#ifndef PIXEL_H
#define PIXEL_H

#include "Vec3.h"
#include "settings.h"

class Pixel : public Vec3 {
  using Vec3::Vec3; // inherit all Vec3 constructors

  public:
    float_type r() const { return x(); };
    float_type g() const { return y(); };
    float_type b() const { return z(); };

    Pixel round() {
      return Pixel(std::round(r()), std::round(g()), std::round(b()));
    }
};

#endif /* PIXEL_H */
