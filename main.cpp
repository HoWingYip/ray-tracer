#include "Scene.h"

int main() {
  Scene scene;
  scene.camera.cameraRay = Ray3(Point3(0, 0, 0), Vec3(0, 0, -1));

  scene.outputImg(1920, 1080, 0);
}
