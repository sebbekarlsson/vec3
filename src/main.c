#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/vector3_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  VEC3Buffer b1 = {0};
  VEC3Buffer b2 = {0};
  vec3_buffer_init(&b1);
  vec3_buffer_init(&b2);


  vec3_buffer_push(&b1, VEC3(4, 4, 4));
  vec3_buffer_push(&b1, VEC3(1, 2, 1));
  vec3_buffer_push(&b1, VEC3(0, 0, 0));


  vec3_buffer_push(&b2, VEC3(4, 4, 3));
  vec3_buffer_push(&b2, VEC3(1, 2, 1));
  vec3_buffer_push(&b2, VEC3(0, 1, 0));


  printf("Before:\n");
  for (int64_t i = 0; i < b1.length; i++) {
    VEC3_PRINT(b1.items[i]);
  }

  vec3_buffer_remove_matching(&b1, b2);

  printf("After:\n");
  for (int64_t i = 0; i < b1.length; i++) {
    VEC3_PRINT(b1.items[i]);
  }


  return 0;
}
