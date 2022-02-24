#include <vec3/triangle.h>
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <stdlib.h>


static const float gg[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
static const int LENLEN = 12;

void vec3_triangulate(Vector3** vectors, uint32_t vectors_length, VEC3Triangle* triangles, uint32_t *triangles_length) {

  mat4 rot = GLM_MAT2_IDENTITY_INIT;
  glm_rotate(rot, 30.0f, (vec3){0, 1, 0});

    uint32_t tri_count = 0;
    for (uint32_t i = 0; i < LENLEN*3; i+=3) {
      int ptr = i*3;
      Vector3 v1 = VEC3(gg[ptr], gg[ptr+1], gg[ptr+2]);
      ptr += 3;
      Vector3 v2 = VEC3(gg[ptr], gg[ptr+1], gg[ptr+2]);
      ptr += 3;
      Vector3 v3 = VEC3(gg[ptr], gg[ptr+1], gg[ptr+2]);

      v1.z = -10 + v1.z;
      v2.z = -10 + v2.z;
      v3.z = -10 + v3.z;

      v1.x = 4 + v1.x;
      v2.x = 4 + v2.x;
      v3.x = 4 + v3.x;

/*
      vec3 vv1 = GLM_VEC3_ZERO_INIT; vector3_to_glm(v1, vv1);
      vec3 vv2 = GLM_VEC3_ZERO_INIT; vector3_to_glm(v2, vv2);
      vec3 vv3 = GLM_VEC3_ZERO_INIT; vector3_to_glm(v3, vv3);
      glm_vec3_rotate(vv1, glm_rad(10.0f), (vec3){1, 0, 0});
      glm_vec3_rotate(vv2, glm_rad(10.0f), (vec3){1, 0, 0});
      glm_vec3_rotate(vv3, glm_rad(10.0f), (vec3){1, 0, 0});
      v1 = VEC3(vv1[0], vv1[1], vv1[2]);
      v2 = VEC3(vv2[0], vv2[1], vv2[2]);
      v3 = VEC3(vv3[0], vv3[1], vv3[2]);*/

    VEC3Triangle* triangle = &triangles[tri_count];
    vector3_copy(&triangle->v1, v1);
    vector3_copy(&triangle->v2, v2);
    vector3_copy(&triangle->v3, v3);
    triangles[tri_count] = *triangle;
    tri_count++;
  }
/*

  uint32_t tri_count = 0;
  for (uint32_t i = 0; i < vectors_length; i++) {
    Vector3 v1 = *vectors[i];
    Vector3 v2 = *vectors[(i + 1) % vectors_length];
    Vector3 v3 = *vectors[(i + 2) % vectors_length];
    VEC3Triangle* triangle = &triangles[tri_count];
    vector3_copy(&triangle->v1, v1);
    vector3_copy(&triangle->v2, v2);
    vector3_copy(&triangle->v3, v3);
    triangles[tri_count] = *triangle;
    tri_count++;
  }*/

  *triangles_length = tri_count;
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
