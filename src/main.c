#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/vector4_buffer.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  mat4 m;
  glm_mat4_identity(m);


  vec3_mat4_print(m);

  return 0;
}
