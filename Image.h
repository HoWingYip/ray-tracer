#ifndef IMAGE_H
#define IMAGE_H

#include "Pixel.h"

#include <vector>
#include <cstdint>

class Image {
  public:
    const uint32_t height;
    const uint32_t width;

    Image(uint32_t imgHeight, uint32_t imgWidth) : height(imgHeight), width(imgWidth) {
      pixArray.resize(height);
      for (size_t i = 0; i < height; i++) {
        pixArray[i].resize(width);
      }
    }

    std::vector<Pixel> &operator[](size_t i) {
      return pixArray[i];
    }

  private:
    std::vector<std::vector<Pixel>> pixArray;
};

#endif /* IMAGE_H */
