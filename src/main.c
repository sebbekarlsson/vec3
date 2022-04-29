#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/util.h>

int main(int argc,  char* argv[]) {


  int64_t max_v = int64_max_value((int64_t[]) { 5, 2, 0, 100, 40, 20 }, 6);

  printf("%ld\n", max_v);

  return 0;
}
