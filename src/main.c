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

static float v3_rand_signed(float *g) {
  float v = v3_hash_float(g);
  return (v * 2.0f - 1.0f);
}


static Vector3Batch generate_random_vec3_batch(float *seed, int64_t count) {
  Vector3* vecs = (Vector3*)calloc(count, sizeof(Vector3));

  for (int64_t i = 0; i < count; i++) {
    vecs[i] = VEC3(v3_rand_signed(seed), v3_rand_signed(seed), v3_rand_signed(seed));
  }
  
  return (Vector3Batch){ .items = vecs, .length = count };
}

int main(int argc,  char* argv[]) {

  float seed = 0.39188245f;

  int64_t count = 16;

  Vector3Batch A = generate_random_vec3_batch(&seed, count); 
  Vector3Batch B = generate_random_vec3_batch(&seed, count); 
  Vector3Batch C = generate_random_vec3_batch(&seed, count); 
  

  Vector3Batch R = vector3_batch_mul(vector3_batch_cross(vector3_batch_div(A, B, C), B, C), B, C);
  
  //R = vector3_batch_unit(R, R);
  vector3_batch_print(R, 1, 2, stdout);

  return 0;
}
