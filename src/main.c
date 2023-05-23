#include <math.h>
#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/triangle_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  Vector3 a = VEC3(0.5, 0.0, 0.001);
  Vector3 n = vector3_unit_attempt(a);
  VEC3_PRINT(n);
  return 0;
}
