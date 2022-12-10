#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/triangle_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  Vector3 v = VEC3(0.1f, -0.1f, -0.001f);

  uint64_t hash = vector3_hash(v);

  printf("%ld\n", hash);


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
