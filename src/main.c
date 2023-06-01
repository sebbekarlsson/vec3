#include "cglm/mat3.h"
#include <math.h>
#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/triangle_buffer.h>
#include <vec3/util.h>
#include <string.h>

int main(int argc,  char* argv[]) {


  Vector3 v = vector3_lerp_safe(VEC3(0.1f, -2.5f, 1.1f), VEC3(1.0f, 1.0f, 0.0f), VEC31(200.0f));
  VEC3_PRINT_PRECISE(v);
 
  return 0;
}
