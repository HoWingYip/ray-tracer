#ifndef SCENE_H
#define SCENE_H

#include "Point3.h"
#include "Ray3.h"
#include "Object.h"
#include "Pixel.h"
#include "Image.h"
#include "Camera.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Scene {
  public:
    Camera camera;

    void addObject(const Object &obj) {
      objs.push_back(obj);
    }

    Color getRayColor(Ray3 ray, uint16_t bouncesLeft) {
      // Cast ray and get color. This function is recursive.

      if (bouncesLeft == 0) {
        return Color(0, 0, 0);
      }

      /*
      1. Find first object intersected by ray
      2. If specular reflection:
           Cast reflected ray off of that object by formula incident - 2*normal*dot(incident, normal)
           and find color of reflected ray through a recursive call
         If diffuse reflection:
           Cast reflected ray in random direction and find its color through recursive call
      3. Multiply reflected ray color by object color reflection coefficients to find incident ray color
         (taking into account Lambertian intensity calculation for diffuse reflection)
      4. Return color of incident ray.
      */
    }

    Image renderImg(uint32_t imgWidth, uint32_t imgHeight, int projectionType) {
      Image img(imgHeight, imgWidth);
      for (size_t i = 0; i < imgHeight; i++) {
        std::vector<Pixel> imgRow(imgWidth);
        for (size_t j = 0; j < imgWidth; j++) {
          imgRow[j] = Pixel(255., 255., 0.);
        }
        img[i] = imgRow;
      }

      return img;
    }

    void outputImg(uint32_t imgWidth, uint32_t imgHeight, int projectionType) {
      // TODO: allow projectionType to be set to perspective or orthographic

      Image img = renderImg(imgWidth, imgHeight, projectionType);

      std::ostringstream oss;
      // PPM format only accepts integers for intensity values
      // so truncate all outputted floats to ints
      oss << std::fixed << std::setprecision(0);

      oss << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

      for (int i = 0; i < imgHeight; i++) {
        if ((i+1) % 100 == 0) {
          std::cout << "Rendering row " << i+1 << " of " << imgHeight << '\n';
        }
        
        for (int j = 0; j < imgWidth; j++) {
          // our ostringstream truncates floats, but let's round them before outputting
          // for greater color accuracy
          oss << img[i][j].round() << ' ';
        }
      }

      std::cout << "Converting to PNG\n";

      FILE *pipe = popen("pnmtopng > output.png", "w");
      if (!pipe) {
        std::cerr << "Couldn't start pnmtopng\n";
        return;
      }
      
      std::string imgStr = oss.str();
      fwrite(imgStr.data(), sizeof(char), imgStr.size(), pipe);
    }

  private:
    std::vector<Object> objs;
};

#endif /* SCENE_H */
