#include <math.h>
#include <stdio.h>
#include <vec3/macros.h>
#include <vec3/vec3.h>
#include <vec3/util.h>

void vector3_copy(Vector3 *dest, Vector3 src) {
  dest->x = src.x;
  dest->y = src.y;
  dest->z = src.z;
  dest->w = src.w;
}


Vector3 vector3_add(Vector3 a, Vector3 b) {
  return VEC3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 vector3_sub(Vector3 a, Vector3 b) {
  return VEC3(a.x - b.x, a.y - b.y, a.z - b.z);
}

void vector2_copy(Vector2 *dest, Vector2 src) {
  dest->x = src.x;
  dest->y = src.y;
}

void vector2Double_copy(Vector2Double *dest, Vector2Double src) {
  dest->x = src.x;
  dest->y = src.y;
}

Vector2 vector2_add(Vector2 a, Vector2 b) { return VEC2(a.x + b.x, a.y + b.y); }

void vector3_string(Vector3 a, char *buffer) {
  sprintf(buffer, "(%.1f, %.1f, %.1f)", a.x, a.y, a.z);
}

float vector3_dot(Vector3 a, Vector3 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;
  float dot_z = a.z * b.z;

  float d = dot_x + dot_y + dot_z;

  return (isinf(d) || isnan(d)) ? 0.0f : d;
}

float vector2_dot(Vector2 a, Vector2 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;

  return dot_x + dot_y;
}

Vector3 vector3_cross(Vector3 a, Vector3 b) {
  Vector3 v = VEC3(0, 0, 0);
  v.x = a.y * b.z - a.z * b.y;
  v.y = a.z * b.x - a.x * b.z;
  v.z = a.x * b.y - a.y * b.x;
  return v;
}

Vector3 vector3_scale(Vector3 a, float scale) {
  return VEC3(a.x * scale, a.y * scale, a.z * scale);
}

Vector3 vector3_downscale(Vector3 a, float scale) {
  return VEC3(a.x / scale, a.y / scale, a.z / scale);
}

Vector3 vector3_unit(Vector3 a) {
  float mag = vector3_mag(a);
  if ((fabsf(mag) <= 0.00001f) || isinf(mag) || isnan(mag))
    return VEC3(0, 0, 0);

  return VEC3(a.x / mag, a.y / mag, a.z / mag);
}
float vector3_mag(Vector3 a) {
  float mag = sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2));
  if (isinf(mag) || isnan(mag)) return 0.0f;
  return mag;
}

float vector3_mag_euclidean(Vector3 a) {
  float value = glm_vec3_norm((vec3){a.x, a.y, a.z});

  if (isinf(value) || isnan(value) || value >= FLT_MAX)
    value = 0.000000001f;

  return value;
}

Vector3 *vector3_alloc(Vector3 a) {
  Vector3 *vec = NEW(Vector3);
  vec->x = a.x;
  vec->y = a.y;
  vec->z = a.z;
  vec->w = a.w;
  return vec;
}

Vector3 vector3_mul(Vector3 a, Vector3 b) {
  return VEC3_OP(a, *, b);
}

float vector3_distance2d(Vector3 a, Vector3 b) {
  return (hypotf(b.x - a.x, b.y - a.y));
}

Vector3 vector3_round(Vector3 a) {
  return VEC3(roundf(a.x), roundf(a.y), roundf(a.z));
}

float vector3_angle2d(Vector3 a) {
  float angle = atan2f(a.x, a.y);
  float degrees = 180 * angle / M_PI;
  return degrees;
  // return (float)((int)(360+roundf(degrees))%360);
}


float vector3_sum(Vector3 a) { return a.x + a.y + a.z; }

float vector3_radians(Vector3 a) { return atan2f(a.y, a.x); }

Vector3 vector3_min(Vector3 a, Vector3 b) {

  vec3 mm = GLM_VEC3_ZERO_INIT;
  glm_vec3_minv((vec3){a.x, a.y, a.z}, (vec3){b.x, b.y, b.z}, mm);

  if (vector3_compare(a, VEC3(mm[0], mm[1], mm[2]))) {
    return a;
  } else if (vector3_compare(b, VEC3(mm[0], mm[1], mm[2]))) {
    return b;
  }

  float mag_a = vector3_mag(a);
  float mag_b = vector3_mag(b);

  return mag_a < mag_b ? a : b;
}

Vector3 vector3_max(Vector3 a, Vector3 b) {
  float mag_a = vector3_mag(a);
  float mag_b = vector3_mag(b);

  vec3 mm = GLM_VEC3_ZERO_INIT;
  glm_vec3_maxv((vec3){a.x, a.y, a.z}, (vec3){b.x, b.y, b.z}, mm);

  if (vector3_compare(a, VEC3(mm[0], mm[1], mm[2]))) {
    return a;
  } else if (vector3_compare(b, VEC3(mm[0], mm[1], mm[2]))) {
    return b;
  }

  return mag_a > mag_b ? a : b;
}

float vector3_angle2d_to(Vector3 a, Vector3 b) {
  float angle = atan2f(b.y - a.y, b.x - a.x);
  float degrees = 180 * angle / M_PI;
  return degrees;
  return (float)((int)(360 + roundf(degrees)) % 360);
}

float vector3_length_sq(Vector3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }

Vector3 vector3_project_centroid(Vector3 a, Vector3 normal, Vector3 centroid) {
  float dotscalar = vector3_dot(vector3_sub(a, centroid), normal);
  return vector3_sub(a, vector3_scale(normal, dotscalar));
}

Vector3 vector3_project(Vector3 a, Vector3 b) {
  float deno = vector3_length_sq(a);

  if (deno == 0)
    return VEC3(0, 0, 0);

  float scalar = vector3_dot(b, a) / deno;

  return vector3_scale(a, scalar);
}

Vector3 vector3_lerp(Vector3 from, Vector3 to, Vector3 scale) {
  Vector3 result = VEC3(from.x, from.y, from.z);
  result.x += (to.x - result.x) * scale.x;
  result.y += (to.y - result.y) * scale.y;
  result.z += (to.z - result.z) * scale.z;

  return result;
}

Vector3 vector3_lerp_factor(Vector3 from, Vector3 to, float factor) {
  vec3 result = GLM_VEC3_ZERO_INIT;

  glm_vec3_lerp((vec3){from.x, from.y, from.z}, (vec3){to.x, to.y, to.z},
                factor, result);

  return VEC3(result[0], result[1], result[2]);
}

Vector3 vector3_project_on_plane(Vector3 a, Vector3 normal) {
  Vector3 next_vec = vector3_project(a, normal);
  return vector3_sub(a, next_vec);
}

bool vector3_is_zero(Vector3 a) { return ceilf(vector3_mag(a)) == 0.0f; }

float vector3_distance3d(Vector3 a, Vector3 b) {
  return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
}

float vector3_mag_diff(Vector3 a, Vector3 b) {
  return vector3_mag(a) - vector3_mag(b);
}

void vector3_serialize_int(Vector3 vec, char *buffer) {
  sprintf(buffer, "%d,%d,%d", (int)ceilf(vec.x), (int)ceilf(vec.y),
          (int)ceilf(vec.z));
}

Vector3 vector3_compute_normal(Vector3 v1, Vector3 v2, Vector3 v3) {
  Vector3 e1 = vector3_sub(v2, v1);
  Vector3 e2 = vector3_sub(v3, v1);

  return vector3_cross(e1, e2);
}

bool vector3_compare(Vector3 a, Vector3 b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

void vector3_to_glm(Vector3 a, vec3 dest) {
  dest[0] = a.x;
  dest[1] = a.y;
  dest[2] = a.z;
}

Vector3 vector3_project_onto_mat4(Vector3 a, mat4 b) {
  vec4 dest;
  glm_mat4_mulv(b, (vec4){a.x, a.y, a.z, a.w}, dest);
  Vector3 v = VEC3(dest[0], dest[1], dest[2]);
  v.w = dest[3];
  return v;
}

Vector3 vector3_reflect(Vector3 I, Vector3 N) {
  return vector3_sub(I, vector3_mul(vector3_scale(N, 2.0f), vector3_mul(I, N)));
}

float vector3_angle3d(Vector3 a) {
  Vector3 n = vector3_unit(a);
  return vector3_angle3d_to(VEC3(0, 0, 0), n);
}
float vector3_angle3d_to(Vector3 a, Vector3 b) {
  return glm_vec3_angle((vec3){a.x, a.y, a.z}, (vec3){b.x, b.y, b.z});
}
Vector3 vector3_angle3d_to_radians_vector(Vector3 a, Vector3 b) {

  Vector3 n1 = vector3_unit(a);
  Vector3 n2 = vector3_unit(a);
  Vector3 r = vector3_sub(n1, n2);

  return VEC3(glm_rad(r.x), glm_rad(r.y), glm_rad(r.z));
}

Vector3 vector3_angle3d_to_deg_vector(Vector3 a, Vector3 b) {

  Vector3 n1 = vector3_unit(a);
  Vector3 n2 = vector3_unit(a);
  Vector3 r = vector3_sub(n1, n2);

  return VEC3(glm_deg(glm_rad(r.x)), glm_deg(glm_rad(r.y)), glm_deg(glm_rad(r.z)));
}

Vector3 vector3_xz(Vector3 v) {
  return VEC3(v.x, 0, v.z);
}
Vector3 vector3_find_min_vec(Vector3 *vectors, uint32_t length) {
  Vector3 min = vectors[0];
  float min_mag = INFINITY;

  for (uint32_t i = 0; i < length; i++) {
    Vector3 v = vectors[i];
    float mag = vector3_sum(v);

    if (mag < min_mag) {
      min = v;
      min_mag = mag;
    }
  }

  return min;
}
Vector3 vector3_find_max_vec(Vector3 *vectors, uint32_t length) {
  Vector3 max = vectors[0];
  float max_mag = -INFINITY;

  for (uint32_t i = 0; i < length; i++) {
    Vector3 v = vectors[i];
    float mag = vector3_sum(v);

    if (mag > max_mag) {
      max = v;
      max_mag = mag;
    }
  }

  return max;
}

Vector3 vector3_find_closest_to_point(Vector3 *vectors, uint64_t length,
                                      Vector3 point, int64_t skip_index,
                                      uint64_t *out_index) {
  if (!vectors || !length)
    return point;
  Vector3 closest = point;
  float min_dist = INFINITY;

  for (uint64_t i = 0; i < length; i++) {
    if (skip_index >= 0 && i == skip_index)
      continue;

    Vector3 v = vectors[i];
    float dist = fabsf(vector3_distance3d(v, point));

    if (dist < min_dist) {
      min_dist = dist;
      closest = v;
      *out_index = i;
    }
  }

  return closest;
}

float vector3_get_component(Vector3 vector, int index) {
  switch (index) {
  case 0:
    return vector.x;
    break;
  case 1:
    return vector.y;
    break;
  case 2:
    return vector.z;
    break;
  default: {
    fprintf(stderr, "(vec3): Warning index > 3.\n");
    return 0;
  }; break;
  }

  return 0;
}

Vector3 vector3_avg(Vector3 *vectors, int64_t length) {
  Vector3 avg = VEC3(0, 0, 0);

  if (vectors == 0 || length <= 0)
    return avg;

  for (int64_t i = 0; i < length; i++) {
    avg = vector3_add(avg, vectors[i]);
  }

  return vector3_scale(avg, 1.0f / (float)length);
}

Vector3 vector3_triple_product(Vector3 a, Vector3 b, Vector3 c) {
  return vector3_cross(a, vector3_cross(b, c));
}

static inline bool number_is_bad(float v) {
  return (isinf(v) || isnan(v) || fabsf(v) >= FLT_MAX);
}

static float v_clamp(float v, float min, float max) {
  return fmaxf(min, fminf(max, v));
}

static float v_smoothstep(float edge0, float edge1, float value) {
  value = v_clamp((value - edge0) / (edge1 - edge0), 0.0f, 1.0f);
  return value * value * (3 - 2 * value);
}

Vector3 vector3_smoothstep(Vector3 edge0, Vector3 edge1, Vector3 value) {
  value.x = v_smoothstep(edge0.x, edge1.x, value.x);
  value.y = v_smoothstep(edge0.y, edge1.y, value.y);
  value.z = v_smoothstep(edge0.z, edge1.z, value.z);
  return value;
}

bool vector3_is_inf(Vector3 a) {
  if (number_is_bad(a.x))
    return 1;
  if (number_is_bad(a.y))
    return 1;
  if (number_is_bad(a.z))
    return 1;
  return 0;
}


Vector3 vector3_angle_vector(Vector3 dir, Vector3 up) {
  float yaw = atan2(dir.x, dir.z);
  float pitch = -asinf(dir.y);
  float planeRightX = sinf(yaw);
  float planeRightZ = -cosf(yaw);

  float roll = asinf(up.x * planeRightX + up.z * planeRightZ);

  // If we're twisted upside-down, return a roll in the range +-(pi/2, pi)
  if (up.y < 0) roll = vec3_sign(roll) * M_PI - roll;

  Vector3 v = VEC3(0, 0, 0);

  // Convert radians to degrees.
  v.y = yaw * 180 / M_PI;
  v.x = pitch * 180 / M_PI;
  v.z = roll * 180 / M_PI;

  v.x -= 90.0f;
  v.z -= 90.0f;

  return v;
}

Vector3 vector3_call(Vector3 a, Vector3CallFunction func) {
  return VEC3(func(a.x), func(a.y), func(a.z));
}

Vector3 vector3_mul_mat4(Vector3 a, mat4 m) {
  mat3 m3 = GLM_MAT3_ZERO_INIT;
  glm_mat4_pick3(m, m3);


  vec3 result = GLM_VEC3_ZERO_INIT;

  glm_mat3_mulv(m3, VEC3_GLM(a), result);



  return VEC3(result[0], result[1], result[2]);
}


float vector3_triple_product_scalar(Vector3 a, Vector3 b, Vector3 c) {
  return vector3_dot(a, vector3_cross(b, c));
}

Vector4 vector3_quat(Vector3 dir, Vector3 up) {
  vec4 q = GLM_VEC4_ZERO_INIT;
  glm_quat_for(VEC3_GLM(dir), VEC3_GLM(up), q);
  return VEC4(q[0], q[1], q[2], q[3]);
}


Vector3 vector3_rotate(Vector3 v, float angle, Vector3 axis) {

  float c = cosf(angle);
  float s = sinf(angle);

  Vector3 k = vector3_unit(axis);
  Vector3 v1 = vector3_scale(v, c);
  Vector3 v2 = vector3_cross(k, v);

  v2 = vector3_scale(v2, s);
  v1 = vector3_add(v1, v2);
  v2 = vector3_scale(k, vector3_dot(k, v) * (1.0f - c));

  return vector3_add(v1, v2);
}
