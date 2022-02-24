#ifndef VEC3_TRIANGLE_H
#define VEC3_TRIANGLE_H
#include <vec3/vec3.h>
#include <stdint.h>
typedef struct {
  Vector3 v1;
  Vector3 v2;
  Vector3 v3;
} VEC3Triangle;

typedef struct {
  int64_t vi1;
  int64_t vi2;
  int64_t vi3;
} VEC3TriangleIndexed;

void vec3_triangulate(Vector3** vectors, uint32_t vectors_length, VEC3Triangle* triangles, uint32_t *triangles_length);


void vec3_sort_triangles(VEC3Triangle* triangles, uint32_t length);
#endif
