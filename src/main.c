#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/vector3_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {

  Int64Buffer buffer = {0};
  int64_buffer_init(&buffer);


  int64_buffer_push_unique(&buffer, 1337);
  int64_buffer_push_unique(&buffer, 1337);
  int64_buffer_push_unique(&buffer, 3431);
  int64_buffer_push_unique(&buffer, 1);
  int64_buffer_push_unique(&buffer, 2);
  int64_buffer_push_unique(&buffer, 3);
  int64_buffer_push_unique(&buffer, 2);

  int64_buffer_print(buffer);

  return 0;
}
