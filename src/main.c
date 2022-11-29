#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/triangle_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  printf("%12.6f\n", vector3_dot(VEC3(1.0f, 0.0f, 0.01f), VEC3(0.1f, 0.59f, 1.0f)));

  return 0;

  VEC3TriangleBuffer buffer = {0};
  vec3_triangle_buffer_init(&buffer);


  for (int i = 0; i < 3; i++) {
    vec3_triangle_buffer_push(&buffer, (VEC3Triangle){ .v1 = VEC31(i+1), .v2 = VEC31(i+2), .v3 = VEC31(i+3) });
  }


  VEC3Triangle tri = {0};

  while (vec3_triangle_buffer_pop_out(&buffer, &tri)) {
    VEC3_PRINT(tri.v1);
  }


  return 0;
}
