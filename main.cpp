#include "Point3.h"
#include "Ray3.h"
#include "Object.h"

#include <vector>
#include <string>

class Scene {
  Point3 cameraPos;
  
  std::vector<Object> objs;

  void render(std::string outputPath, int projectionType) {
    // projectionType can be perspective or orthographic
  }
};

int main() {
  
}
