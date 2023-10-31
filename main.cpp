#include "Scene.h"
#include "Sphere.h"
#include "settings.h"

#include <memory>
#include <iostream>

int main() {
  Scene scene;
  // scene.camera.cameraRay = Ray3(Point3(0, 0, 0), Vec3(0, 0, -1));
  scene.camera.focalLength = 500.;
  
  std::shared_ptr<Sphere> sphere1Ptr = std::make_shared<Sphere>(
    Point3(0, 0, -500), 200., Color(255, 0, 255));
  scene.addObject(sphere1Ptr);

  std::cout << "Scene contains " << scene.objects.size() << " objects\n";

  scene.saveImg(1920, 1080, 5, 0);
}
