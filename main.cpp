#include <vector>
#include <string>
#include <cmath>

using float_type = double;

template <typename T>
class Vec3 {
  public:
    Vec3(T x, T y, T z) : v{x, y, z} {}

    inline T x() { return v[0]; }
    inline T y() { return v[1]; }
    inline T z() { return v[2]; }

    inline T operator[](std::size_t i) const { return v[i]; }
    inline T &operator[](std::size_t i) { return v[i]; }

    inline T lengthSquared() {
      return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }

    inline T length() {
      return std::sqrt(lengthSquared());
    }

    inline T norm() {
      return *this / length();
    }

    inline Vec3 operator+(const Vec3 &other) {
      return Vec3(v[0]+other.v[0], v[1]+other.v[1], v[2]+other.v[2]);
    }
    inline Vec3 operator+=(const Vec3 &other) {
      v[0] += other.v[0];
      v[1] += other.v[1];
      v[2] += other.v[2];
      return *this;
    }

    inline Vec3 operator-() {
      return Vec3(-v[0], -v[1], -v[2]);
    }

    inline Vec3 operator-(const Vec3 &other) {
      return *this + (-other);
    }
    inline Vec3 operator-=(const Vec3 &other) {
      *this += -other;
      return *this;
    }

    inline Vec3 operator*(float_type k) {
      return Vec3(k*v[0], k*v[1], k*v[2]);
    }
    inline Vec3 operator*=(float_type k) {
      v[0] *= k;
      v[1] *= k;
      v[2] *= k;
    }

    inline Vec3 operator*(const Vec3 &other) {
      return Vec3(v[0]*other[0], v[1]*other[1], v[2]*other[2]);
    }
    inline Vec3 operator*=(const Vec3 &other) {
      v[0] *= other.v[0];
      v[1] *= other.v[1];
      v[2] *= other.v[2];
      return *this;
    }

    inline Vec3 operator/(float_type k) {
      return *this * (1/k);
    }
    inline Vec3 operator/=(float_type k) {
      *this *= (1/k);
      return *this;
    }
  
  private:
    T v[3];
};

template <typename T> using Point3 = Vec3<T>;

template <typename T>
class Ray3 {
  Vec3<T> base;
  Vec3<T> direction;

  Ray3(Vec3<T> a_, Vec3<T> d_) : base(a_), direction(d_) {}

  Point3<T> produce(float_type t) {
    return base + t*direction;
  }
};

class Object {
  template <typename T>
  std::pair<bool, Point3<T>> rayIntersect(Ray3<T> ray);
};

class Sphere : Object {
  Point3<float_type> center;
  float_type radius;

  Sphere(Point3<float_type> c_, float_type r_) : center(c_), radius(r_) {}

  template <typename T>
  std::pair<bool, Point3<T>> rayIntersect(Ray3<T> ray) {
    
  }

  template <typename T>
  Ray3<T> normal(Point3<T> hitPoint) {
    return (hitPoint - center).norm();
  }
};

class Scene {
  Vec3<float_type> cameraPos;
  
  std::vector<Object> objs;

  void render(std::string outputPath, int projectionType) {
    // projectionType can be perspective or orthographic
  }
};

int main() {
  
}
