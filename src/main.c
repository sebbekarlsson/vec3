#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  VEC4Buffer buffer = {0};
  vec4_buffer_init(&buffer);


  vec4_buffer_push(&buffer, VEC4(1, 2, 3, 4));


  VEC4_PRINT_PRECISE(buffer.items[0]);

  return 0;
}
