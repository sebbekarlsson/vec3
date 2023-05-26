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


  mat3 m = GLM_MAT3_IDENTITY_INIT;

  const int cap = 360;
  m[2][1] = 0.49281f;
  m[0][0] = 3.3929812f;
  char buff[cap];
  memset(&buff[0], 0, cap*sizeof(char));
  vec3_mat3_to_string(m, buff, cap);

  printf("%s\n", buff);
 
  return 0;
}
