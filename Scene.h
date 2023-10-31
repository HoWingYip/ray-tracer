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
#include <memory>

class Scene {
  public:
    Camera camera;
    std::vector<std::shared_ptr<Object>> objects;

    void addObject(std::shared_ptr<Object> objPtr) {
      objects.push_back(objPtr);
    }

    Color getRayColor(Ray3 ray, uint16_t bouncesLeft) {
      // Cast ray and get color. This function is recursive.
      // std::cout << "Tracing ray (" << ray.base << "), (" << ray.direction << ")\n";

      if (bouncesLeft == 0) {
        return Color(0, 0, 0);
      }

      std::shared_ptr<Object> firstIntersectObjPtr(nullptr);
      float_type prevMinT = INFINITY;
      for (const std::shared_ptr<Object> &objPtr : objects) {
        auto [doesIntersect, t] = objPtr->findIntersectParam(ray.norm());
        // std::cout << doesIntersect << ' ' << t << '\n';
        if (doesIntersect && t < prevMinT) {
          firstIntersectObjPtr = objPtr;
          prevMinT = t;
        }
      }

      if (firstIntersectObjPtr != nullptr) {
        return Color(255, 0, 0);
      } else {
        return Color(0, 0, 255);
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

    Image renderImg(uint32_t imgWidth, uint32_t imgHeight, uint16_t maxBounces, int projectionType) {
      // start at top left
      float_type topLeftX = -((float_type)(imgWidth - 1)) / 2;
      float_type topLeftY = ((float_type)(imgHeight - 1)) / 2;

      Vec3 dx(1, 0, 0);
      Vec3 dy(0, -1, 0);

      Point3 currPixelVec(topLeftX, topLeftY, -camera.focalLength);

      Image img(imgHeight, imgWidth);

      for (uint32_t i = 0; i < imgHeight - 1; i++) {
        currPixelVec.setX(topLeftX);
        for (uint32_t j = 0; j < imgWidth - 1; j++) {
          std::cout << currPixelVec << '\n';

          img[i][j] = getRayColor(Ray3(Vec3(0, 0, 0), currPixelVec), maxBounces);
          currPixelVec += dx;
        }
        currPixelVec += dy;
      }

      return img;
    }

    void saveImg(uint32_t imgWidth, uint32_t imgHeight, uint16_t maxBounces, int projectionType) {
      // TODO: allow projectionType to be set to perspective or orthographic

      Image img = renderImg(imgWidth, imgHeight, maxBounces, projectionType);

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
};

#endif /* SCENE_H */
