#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/vector3_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {

  Vector3 v = VEC3(180, 360, 270);
  Vector3 v2 = vector3_call(v, glm_rad);

  VEC3_PRINT(v2);

  return 0;
}
