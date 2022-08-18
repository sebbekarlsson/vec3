#ifndef VEC3_H
#define VEC3_H
#include <cglm/call.h>
#include <cglm/cglm.h>
#include <stdint.h>

#define VECTOR3_SERIALIZE_CAP 256

typedef struct {
  float x;
  float y;
  float z;
  float u;
  float v;
  float w;
} Vector3;

typedef struct {
  Vector3 a;
  Vector3 b;
} Vector3Pair;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vector4;

typedef struct {
  float x;
  float y;
} Vector2;

typedef struct {
  long double x;
  long double y;
} Vector2Double;

typedef struct {
  int64_t x;
  int64_t y;
} Vector2i64;

typedef struct {
  uint64_t x;
  uint64_t y;
} Vector2ui64;

typedef struct {
  Vector3 furthest;
  Vector3 closest;

  int64_t furthest_index;
  int64_t closest_index;
} Vector3Support;

typedef struct {
  Vector3Support a;
  Vector3Support b;
  Vector3 point;
} Vector3SupportPair;

typedef struct {
  int64_t index;
  Vector3 v;
} Vector3Indexed;

typedef struct {
  int64_t index_a;
  int64_t index_b;

  Vector3 a;
  Vector3 b;
} Vector3PairIndexed;

void vector3_copy(Vector3 *dest, Vector3 src);
Vector3 vector3_add(Vector3 a, Vector3 b);
Vector3 vector3_sub(Vector3 a, Vector3 b);
Vector3 vector3_scale(Vector3 a, float scale);
Vector3 vector3_downscale(Vector3 a, float scale);
Vector3 vector3_min(Vector3 a, Vector3 b);
Vector3 vector3_max(Vector3 a, Vector3 b);
Vector3 vector3_mul(Vector3 a, Vector3 b);

Vector3Pair vector3_min_max(Vector3 a, Vector3 b);

float vector3_sum(Vector3 a);
float vector3_angle2d_to(Vector3 a, Vector3 b);
Vector3 vector3_normal(Vector3 a);
Vector3 vector3_normalize(Vector3 a);
Vector3 vector3_lerp(Vector3 from, Vector3 to, Vector3 scale);

Vector3 vector3_lerp_factor(Vector3 from, Vector3 to, float factor);

float vector3_radians(Vector3 a);
Vector3 vector3_round(Vector3 a);
float vector3_angle2d(Vector3 a);
float vector3_angle3d(Vector3 a);
float vector3_angle3d_to(Vector3 a, Vector3 b);
Vector3 vector3_angle3d_to_radians_vector(Vector3 a, Vector3 b);
Vector3 vector3_angle3d_to_deg_vector(Vector3 a, Vector3 b);
Vector3 vector3_unit(Vector3 a);
float vector3_mag(Vector3 a);
Vector3 *vector3_alloc(Vector3 a);
void vector3_string(Vector3 a, char *buffer);
Vector3 vector3_project_centroid(Vector3 a, Vector3 normal, Vector3 centroid);
Vector3 vector3_compute_normal(Vector3 v1, Vector3 v2, Vector3 v3);
unsigned int vector3_is_zero(Vector3 a);
float vector3_dot(Vector3 a, Vector3 b);
unsigned int vector3_compare(Vector3 a, Vector3 b);
Vector3 vector3_cross(Vector3 a, Vector3 b);
float vector3_distance2d(Vector3 a, Vector3 b);
float vector3_distance3d(Vector3 a, Vector3 b);
float vector3_mag_diff(Vector3 a, Vector3 b);
Vector3 vector3_project(Vector3 a, Vector3 b);
void vector3_to_glm(Vector3 a, vec3 dest);
Vector3 vector3_project_on_plane(Vector3 a, Vector3 normal);
void vector3_serialize_int(Vector3 vec, char *buffer);

Vector3 vector3_project_onto_mat4(Vector3 a, mat4 b);

Vector3 vector3_reflect(Vector3 I, Vector3 N);

Vector3 vector3_xz(Vector3 v);

void vector2_copy(Vector2 *dest, Vector2 src);
void vector2Double_copy(Vector2Double *dest, Vector2Double src);
Vector2 vector2_add(Vector2 a, Vector2 b);

Vector3 vector_downscale(Vector3 a, float scale);


Vector3 vector3_find_min_vec(Vector3* vectors, uint32_t length);
Vector3 vector3_find_max_vec(Vector3* vectors, uint32_t length);

Vector3 vector3_find_closest_to_point(Vector3* vectors, uint64_t length, Vector3 point, int64_t skip_index, uint64_t* out_index);

Vector3 vector3_avg(Vector3* vectors, int64_t length);


float vector3_get_component(Vector3 vector, int index);
Vector3 vector3_triple_product(Vector3 a, Vector3 b, Vector3 c);

Vector3 vector3_angle_vector(Vector3 dir, Vector3 up);
float vector3_mag_euclidean(Vector3 a);
Vector3 vector3_smoothstep(Vector3 edge0, Vector3 edge1, Vector3 value);


float vector3_diff_percentage(Vector3 a, Vector3 b);

unsigned int vector3_is_inf(Vector3 a);

typedef float (*Vector3CallFunction)(float v);
Vector3 vector3_call(Vector3 a, Vector3CallFunction func);


#define VEC3_OP(a, op, b) ((Vector3){a.x op b.x, a.y op b.y, a.z op b.z})
#define VEC3_OP_SR(a, op, b) ((Vector3){a.x op b, a.y op b, a.z op b})

#define VEC3_ALLOC(a) (vector3_alloc(a))
#define VEC3_PRINT(a)                                                          \
  { printf("(%2.2f, %2.2f, %2.2f)\n", a.x, a.y, a.z); }

#define VEC3_EMPTY ((Vector3){0, 0, 0})

#define VEC3(x, y, z) ((Vector3){x, y, z})
#define VEC31(V)(VEC3(V, V, V))
#define VEC2(x, y) ((Vector2){x, y})

#define VEC3_GLM(v)((vec3){ v.x, v.y, v.z })

#endif
