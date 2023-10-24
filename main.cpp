#include "Point3.h"
#include "Ray3.h"
#include "Object.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <array>

using Pixel = std::array<uint8_t, 3>;
using Image = std::vector<std::vector<Pixel>>;

std::ostream &operator<<(std::ostream &os, Pixel &p) {
  os << std::to_string(p[0]) << ' ' << std::to_string(p[1]) << ' ' << std::to_string(p[2]);
  return os;
}

class Scene {
  public:
    Point3 cameraPos;
    
    std::vector<Object> objs;

    Image renderImg(uint32_t imgWidth, uint32_t imgHeight, int projectionType) {
      Image img(imgHeight);
      for (int i = 0; i < imgHeight; i++) {
        std::vector<Pixel> imgRow(imgWidth);
        for (int j = 0; j < imgWidth; j++) {
          imgRow[j] = {255, 0, 255};
        }
        img[i] = imgRow;
      }

      return img;
    }

    void outputImg(uint32_t imgWidth, uint32_t imgHeight, int projectionType) {
      // TODO: projectionType can be perspective or orthographic
      Image img = renderImg(imgWidth, imgHeight, projectionType);

      std::ostringstream oss;

      // P3 means colours are in ASCII and each channel can take on 256 intensity values (0-255)
      // 255 is max intensity of the pixels we're gonna output
      // see https://en.wikipedia.org/wiki/Netpbm
      oss << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

      // pixels are written left to right, then top to bottom
      // like normal 2D array output
      for (int i = 0; i < imgHeight; i++) {
        for (int j = 0; j < imgWidth; j++) {
          oss << img[i][j] << ' ';
        }
      }

      std::string imgStr = oss.str();

      FILE *pipe = popen("pnmtopng > output.png", "w");
      if (!pipe) {
        std::cerr << "Couldn't start pnmtopng\n";
        return;
      }
      fwrite(imgStr.data(), sizeof(char), imgStr.size(), pipe);
    }
};

int main() {
  Scene scene;
  scene.outputImg(1920, 1080, 0);
}
