#include <vec3/util.h>
#include <math.h>

uint64_t floats_min_index(float* floats, uint64_t length) {
  float min_v = INFINITY;
  uint32_t min_index = 0;

  for (uint64_t i = 0; i < length; i++) {
    if (floats[i] < min_v) {
      min_v = floats[i];
      min_index = i;
    }
  }

  return min_index;
}

int64_t int64_max_value(int64_t* ints, uint64_t length) {

  int64_t max_v = (int64_t)-INFINITY;


  for (uint64_t i = 0; i < length; i++) {

    if (ints[i] > max_v) {
      max_v = ints[i];
    }
  }

  return max_v;
}
