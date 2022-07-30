#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/vector3_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {

  Vector3 a = VEC3(0, -1, 0);

  Vector3 b = VEC3(0, 0, 0);


  Vector3 max = vector3_max(a, b);
  Vector3 min = vector3_min(a, b);


  printf("max:\n");
  VEC3_PRINT(max);
  printf("min:\n");
  VEC3_PRINT(min);

  return 0;
}
