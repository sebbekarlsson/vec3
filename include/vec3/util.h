#ifndef VEC3_UTIL_H
#define VEC3_UTIL_H
#include <stdint.h>
uint64_t floats_min_index(float* floats, uint64_t length);

int64_t int64_max_value(int64_t* ints, uint64_t length);


float vec3_sign(float v);
#endif
