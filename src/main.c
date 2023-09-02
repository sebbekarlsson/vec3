#include "cglm/mat3.h"
#include <math.h>
#include <vec3/vec3.h>
#include <vec3/triangle.h>
#include <vec3/buffers.h>
#include <vec3/matrix.h>
#include <vec3/vector3_buffer.h>
#include <vec3/batch.h>
#include <vec3/vector4_buffer.h>
#include <vec3/triangle_buffer.h>
#include <vec3/util.h>
#include <string.h>

static uint32_t v3_hash_uint(uint32_t x) {
  uint32_t y = ~x;
  x ^= x << 17U;
  x ^= x >> 13U;
  x ^= x << 5U;
  x ^= x >> 3U;
  x += ((x * 301U + y) * 3981U + (y >> 3U));
  return x * 9381U;
}

static uint32_t v3_float32_bits_to_uint32(float f) {
  union V3FloatUint32 {
    float f;
    uint32_t i;
  };
  union V3FloatUint32 converted;
  converted.f = f;
  return converted.i;
}

static float v3_hash_float(float* g) {
  uint32_t y = v3_hash_uint(v3_float32_bits_to_uint32(*g));

  float next = (float)y / (float)0xFFFFFFFFU;

  *g = next;
  
  return next;
}

static float v3_rand_signed(uint32_t* seed) {
  *seed = v3_hash_uint(*seed);
  float v = ((float)*seed) / (float)0xFFFFFFFFU;
  return (v * 2.0f - 1.0f);
}


#define RANDOM_VEC3(seed) VEC3(v3_rand_signed(seed), v3_rand_signed(seed), v3_rand_signed(seed))


int main(int argc,  char* argv[]) {


  uint32_t seed = 39281U;
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  VEC3_PRINT_PRECISE(vector3_saturate(VEC31(v3_rand_signed(&seed))));
  VEC3_PRINT_PRECISE(VEC31(v3_rand_signed(&seed)));
  return 0;
  
  int count = 16;

  for (int i = 0; i < count; i++) {
    Vector3 v = RANDOM_VEC3(&seed);
    v = vector3_scale(v, -200000.0f);
    printf("mag: %12.6f\n", vector3_mag(v));
  }

  return 0;
}
