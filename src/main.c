#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  Vector3 a = VEC3(1, 1000, 10);

  Vector3 b = VEC3(100, 100, -100);


  float diff = vector3_diff_percentage(a, b);

  printf("%12.6f\n", diff);


  return 0;
}
