#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  Vector3 a = VEC3(0, 0, 0);
  Vector3 b = VEC3(0, 90, 90);

  Vector3 angle_vec = vector3_angle_vector(a, b);

  VEC3_PRINT(angle_vec);

  return 0;
}
