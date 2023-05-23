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


  Vector3 a = VEC3(0.0000000000000000000000000000000001f, 0.0f, 0.0000000000000000001f);
  Vector3 n = vector3_unit(a);


  VEC3_PRINT_PRECISE(n);
 
  return 0;
}
