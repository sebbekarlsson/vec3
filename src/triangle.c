#include <vec3/triangle.h>
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <stdlib.h>


void vec3_triangulate(Vector3* vectors, uint32_t vectors_length, VEC3Triangle* triangles, uint32_t *triangles_length) {

  uint32_t tri_count = 0;
  for (uint32_t i = 0; i < vectors_length; i++) {
    Vector3 v1 = vectors[i];
    Vector3 v2 = vectors[(i + 1) % vectors_length];
    Vector3 v3 = vectors[(i + 2) % vectors_length];
    VEC3Triangle* triangle = &triangles[tri_count];
    vector3_copy(&triangle->v1, v1);
    vector3_copy(&triangle->v2, v2);
    vector3_copy(&triangle->v3, v3);
    tri_count++;
  }

}


static int compare_triangles(const void *a, const void *b) {
  VEC3Triangle *res_a = (VEC3Triangle *)a;
  VEC3Triangle *res_b = (VEC3Triangle *)b;


  float minZ_a = INFINITY;
  float maxZ_a = -INFINITY;

  minZ_a = fminf(minZ_a, res_a->v1.z);
  minZ_a = fminf(minZ_a, res_a->v2.z);
  minZ_a = fminf(minZ_a, res_a->v3.z);

  maxZ_a = fmaxf(maxZ_a, res_a->v1.z);
  maxZ_a = fmaxf(maxZ_a, res_a->v2.z);
  maxZ_a = fmaxf(maxZ_a, res_a->v3.z);


  float minZ_b = INFINITY;
  float maxZ_b = -INFINITY;


  minZ_b = fminf(minZ_b, res_b->v1.z);
  minZ_b = fminf(minZ_b, res_b->v2.z);
  minZ_b = fminf(minZ_b, res_b->v3.z);

  maxZ_b = fmaxf(maxZ_b, res_b->v1.z);
  maxZ_b = fmaxf(maxZ_b, res_b->v2.z);
  maxZ_b = fmaxf(maxZ_b, res_b->v3.z);

  return res_a->v1.z - res_b->v1.z;
}

void sort_triangles(VEC3Triangle* triangles, uint32_t length) {
  if (length <= 0) return;
  qsort(triangles, length, sizeof(VEC3Triangle), compare_triangles);
}

Vector3 vec3_triangle_get_area(VEC3Triangle triangle) {
  float min_x = fminf(fminf(triangle.v1.x, triangle.v2.x), triangle.v3.x);
  float min_y = fminf(fminf(triangle.v1.y, triangle.v2.y), triangle.v3.y);
  float min_z = fminf(fminf(triangle.v1.z, triangle.v2.z), triangle.v3.z);


  float max_x = fmaxf(fmaxf(triangle.v1.x, triangle.v2.x), triangle.v3.x);
  float max_y = fmaxf(fmaxf(triangle.v1.y, triangle.v2.y), triangle.v3.y);
  float max_z = fmaxf(fmaxf(triangle.v1.z, triangle.v2.z), triangle.v3.z);



  return vector3_sub(VEC3(max_x, max_y, max_z), VEC3(min_x, min_y, min_z));
}
