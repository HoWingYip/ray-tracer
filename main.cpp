#include "Scene.h"
#include "Sphere.h"
#include "settings.h"

#include <memory>
#include <iostream>

int main() {
  Scene scene;
  // scene.camera.cameraRay = Ray3(Point3(0, 0, 0), Vec3(0, 0, -1));
  scene.camera.focalLength = 500.;

  scene.addObject(std::make_shared<Sphere>(
    Point3(0, 0, -1000), 200., Color(128, 0, 128)
  ));

  scene.addObject(std::make_shared<Sphere>(
    Point3(0, -10200, -1000), 10000, Color(200, 0, 0)
  ));

  std::cout << "Scene contains " << scene.objects.size() << " objects\n";

  scene.saveImg(640, 480, 10, 0);
}
