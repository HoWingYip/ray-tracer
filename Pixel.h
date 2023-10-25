#ifndef PIXEL_H
#define PIXEL_H

#include "Vec3.h"
#include "settings.h"

#include <ostream>

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

std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {
  os << pixel.r() << ' ' << pixel.g() << ' ' << pixel.b();
  return os;
}

#endif /* PIXEL_H */
