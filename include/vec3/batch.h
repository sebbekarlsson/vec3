#ifndef VEC3_BATCH_H
#define VEC3_BATCH_H
#include <vec3/vec3.h>
#include <stdio.h>

typedef struct {
  Vector3* items;
  int64_t length;
} Vector3Batch;

typedef struct {
  float* items;
  int64_t length;
} Vector3FloatBatch;

Vector3Batch vector3_batch_add(Vector3Batch a, Vector3Batch b, Vector3Batch out);

Vector3Batch vector3_batch_sub(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out);

Vector3Batch vector3_batch_mul(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out);

Vector3Batch vector3_batch_div(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out);

Vector3Batch vector3_batch_cross(Vector3Batch vecs_a, Vector3Batch vecs_b,
                         Vector3Batch out);

Vector3Batch vector3_batch_unit(Vector3Batch vecs_a, Vector3Batch out);

Vector3Batch vector3_batch_scale(Vector3Batch vecs_a, Vector3FloatBatch scales,
                         Vector3Batch out);

Vector3FloatBatch vector3_batch_dot(Vector3Batch vecs_a, Vector3Batch vecs_b,
                         Vector3FloatBatch out);


void vector3_batch_print(Vector3Batch vecs, int columns, int precision, FILE* fp);

#endif
