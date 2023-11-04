#ifndef SCENE_H
#define SCENE_H

#include "Ray3.h"
#include "Object.h"
#include "Pixel.h"
#include "Image.h"
#include "Camera.h"
#include "settings.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <memory>

class Scene {
  public:
    Camera camera;
    std::vector<std::shared_ptr<Object>> objects;

    void addObject(std::shared_ptr<Object> objPtr) {
      objects.push_back(objPtr);
    }

    Color getRayColor(Ray3 ray, uint16_t bouncesLeft) {
      if (bouncesLeft == 0) {
        return Color(0, 0, 0);
      }

      // TODO: implement HitRecord?
      std::shared_ptr<Object> firstIntersectObjPtr(nullptr);
      Point3 intersectPoint;
      float_type minT = INFINITY;
      for (const std::shared_ptr<Object> &objPtr : objects) {
        auto [doesIntersect, currIntersectPoint, t] = objPtr->findIntersectParam(ray.norm());
        // std::cout << doesIntersect << ' ' << t << '\n';
        if (doesIntersect && t < minT) {
          firstIntersectObjPtr = objPtr;
          intersectPoint = currIntersectPoint;
          minT = t;
        }
      }

      // if no intersection with any object, return ambient ray
      if (firstIntersectObjPtr == nullptr) {
        float_type y = (ray.direction.norm().y() + 1.) / 2;
        return (1-y)*Color(99, 52, 200) + y*Color(255, 255, 255);
      }

      Vec3 normalDir = firstIntersectObjPtr->normal(intersectPoint).direction;
      Ray3 incomingRay(intersectPoint, ray.direction - 2*dot(normalDir, ray.direction)*normalDir);
      
      return firstIntersectObjPtr->color / 255. * getRayColor(incomingRay, bouncesLeft-1);
    }

    Image renderImg(uint32_t imgWidth, uint32_t imgHeight, uint16_t maxBounces, int projectionType) {
      // start at top left
      float_type topLeftX = -((float_type)(imgWidth - 1)) / 2;
      float_type topLeftY = ((float_type)(imgHeight - 1)) / 2;
      
      Point3 currPixelVec(topLeftX, topLeftY, -camera.focalLength);
      Image img(imgHeight, imgWidth);

      Vec3 dx(1, 0, 0);
      Vec3 dy(0, -1, 0);

      for (uint32_t i = 0; i < imgHeight - 1; i++) {
        if ((i+1) % 100 == 0) {
          std::cout << "Rendering row " << i+1 << " of " << imgHeight << '\n';
        }

        currPixelVec.setX(topLeftX);

        for (uint32_t j = 0; j < imgWidth - 1; j++) {
          Color currPixelColor = Color(0, 0, 0);
          // Multi-sample anti-aliasing (MSAA). TODO: implement in parallel!
          for (uint16_t k = 0; k < samplesPerPixel; k++) {
            Vec3 sampleVec = currPixelVec + Vec3::random(-0.5, 0.5);
            currPixelColor += getRayColor(Ray3(Vec3(0, 0, 0), sampleVec), maxBounces);
          }
          currPixelColor /= samplesPerPixel;

          img[i][j] = currPixelColor;
          currPixelVec += dx;
        }
        currPixelVec += dy;
      }

      return img;
    }

    void saveImg(uint32_t imgWidth, uint32_t imgHeight, uint16_t maxBounces, int projectionType) {
      // TODO: allow projectionType to be set to perspective or orthographic

      Image img = renderImg(imgWidth, imgHeight, maxBounces, projectionType);

      std::ofstream ofs("output.ppm");

      // PPM format only accepts integers for intensity values
      // so truncate all outputted floats to ints
      ofs << std::fixed << std::setprecision(0);

      ofs << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

      for (int i = 0; i < imgHeight; i++) {        
        for (int j = 0; j < imgWidth; j++) {
          // our ostringstream truncates floats, but let's round them before outputting
          // for greater color accuracy
          ofs << img[i][j].round() << '\n';
        }
      }

      ofs.flush();

      std::cout << "Converting to PNG\n";
      system("pnmtopng output.ppm > output.png");
    }
};

#endif /* SCENE_H */
