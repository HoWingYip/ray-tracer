#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "settings.h"

#include <ostream>

class Color : public Vec3 {
  using Vec3::Vec3; // inherit all Vec3 constructors

  public:
    float_type r() const { return x(); };
    float_type g() const { return y(); };
    float_type b() const { return z(); };

    Color round() {
      return Color(std::round(r()), std::round(g()), std::round(b()));
    }
};

#endif /* PIXEL_H */
