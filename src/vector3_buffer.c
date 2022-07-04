#include <stdlib.h>
#include <string.h>
#include <vec3/macros.h>
#include <vec3/vector3_buffer.h>

void vec3_buffer_init(VEC3Buffer *buffer) {
  if (buffer->initialized)
    return;
  buffer->items = 0;
  buffer->length = 0;
  buffer->never_generate_normals = 0;
  buffer->normals = 0;
  buffer->normals_length = 0;
  buffer->ref_count = 0;
  buffer->initialized = 1;
}

#define VECTOR_BUFFER_GUARD(buffer)                                            \
  {                                                                            \
    if (!buffer->initialized) {                                                \
      fprintf(stderr, "This vector buffer is not initialized! (%s)\n",         \
              __func__);                                                       \
    }                                                                          \
  }

int vec3_buffer_push(VEC3Buffer *buffer, Vector3 v) {
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items =
      (Vector3 *)realloc(buffer->items, (buffer->length + 1) * sizeof(Vector3));
  buffer->items[buffer->length] = v;
  buffer->length++;

  return buffer->length > 0 && buffer->items != 0;
}

int vec3_buffer_concat_vectors_front(VEC3Buffer *buffer, Vector3 *vectors,
                                     int64_t len) {
  if (!len || !vectors)
    return 0;
  VECTOR_BUFFER_GUARD(buffer);

  VEC3Buffer next_buffer = {0};
  vec3_buffer_init(&next_buffer);

  vec3_buffer_concat_vectors(&next_buffer, vectors, len);

  if (!vec3_buffer_is_empty(*buffer)) {
    vec3_buffer_concat_vectors(&next_buffer, buffer->items, buffer->length);
  }

  vec3_buffer_clear(buffer);

  *buffer = next_buffer;

  return buffer->length > 0 && buffer->items != 0;
}

int vec3_buffer_concat_vectors(VEC3Buffer *buffer, Vector3 *vectors,
                               int64_t len) {
  if (!len || !vectors)
    return 0;
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items = (Vector3 *)realloc(buffer->items,
                                     (buffer->length + len) * sizeof(Vector3));
  memcpy(&buffer->items[buffer->length], &vectors[0], len * sizeof(Vector3));
  buffer->length += len;

  return buffer->length > 0 && buffer->items != 0;
}

Vector3 *vec3_buffer_get_normals(VEC3Buffer *buffer, int64_t *len) {
  VECTOR_BUFFER_GUARD(buffer);
  *len = 0;
  if (buffer->never_generate_normals)
    return 0;
  if (buffer->normals && buffer->normals_length > 0) {
    *len = buffer->normals_length;
    return buffer->normals;
  }

  vec3_buffer_generate_normals(buffer);

  *len = buffer->normals_length;

  return buffer->normals;
}

int vec3_buffer_generate_normals(VEC3Buffer *buffer) {
  VECTOR_BUFFER_GUARD(buffer);
  if (buffer->never_generate_normals)
    return 0;
  if (buffer->normals && buffer->normals_length)
    return 1;
  if (!buffer->items || !buffer->length)
    return 0;
  if (buffer->normals)
    free(buffer->normals);

  buffer->normals = 0;
  buffer->normals_length = 0;

  buffer->normals = (Vector3 *)calloc(buffer->length / 3, sizeof(Vector3));

  for (int64_t i = 0; i < buffer->length; i += 3) {
    Vector3 v1 = buffer->items[i];
    Vector3 v2 = buffer->items[i + 1];
    Vector3 v3 = buffer->items[i + 2];
    Vector3 normal = vector3_compute_normal(v1, v2, v3);
    buffer->normals[buffer->normals_length] = normal;
    buffer->normals_length += 1;
  }

  return buffer->normals != 0 && buffer->length > 0;
}

int vec3_buffer_translate(VEC3Buffer *buffer, Vector3 pos,
                          VEC3Rotation rotation) {
  if (!buffer->length || !buffer->items)
    return 0;
  VECTOR_BUFFER_GUARD(buffer);
  return vec3_array_translate(buffer->items, buffer->length, pos, rotation);
}

int vec3_buffer_copy(VEC3Buffer *dest, VEC3Buffer src) {
  if (!vec3_buffer_is_empty(*dest)) {
    fprintf(stderr, "Cannot copy into non-empty vector buffer.\n");
    return 0;
  }
  if (!src.length || !src.items)
    return 0;
  if (!dest->initialized)
    vec3_buffer_init(dest);
  return vec3_buffer_concat_vectors(dest, src.items, src.length);
}

int vec3_buffer_translate_copy(VEC3Buffer *dest, VEC3Buffer src, Vector3 pos,
                               VEC3Rotation rotation) {
  if (!vec3_buffer_is_empty(*dest)) {
    fprintf(stderr, "Cannot copy into non-empty vector buffer.\n");
    return 0;
  }
  vec3_buffer_init(dest);
  if (!vec3_buffer_copy(dest, src))
    return 0;
  return vec3_buffer_translate(dest, pos, rotation);
}

unsigned int vec3_buffer_is_empty(VEC3Buffer buffer) {
  return buffer.length <= 0 || buffer.items == 0;
}
int vec3_buffer_clear(VEC3Buffer *buffer) {
  VECTOR_BUFFER_GUARD(buffer);

  if (buffer->ref_count > 0)
    return 0;

  if (!vec3_buffer_is_empty(*buffer)) {
    free(buffer->items);
    buffer->items = 0;
    buffer->length = 0;
  }

  if (buffer->normals && buffer->normals_length) {
    free(buffer->normals);
    buffer->normals = 0;
    buffer->normals_length = 0;
  }

  return 1;
}

int vec3_buffer_allocate(VEC3Buffer *buffer, int64_t n) {
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items =
      (Vector3 *)realloc(buffer->items, (buffer->length + n) * sizeof(Vector3));
  return buffer->items != 0;
}

void vec3_buffer_never_generate_normals(VEC3Buffer *buffer) {
  buffer->never_generate_normals = 1;
}

int vec3_buffer_splice(VEC3Buffer *buffer, int start, Vector3 point) {
  VECTOR_BUFFER_GUARD(buffer);
  int right = buffer->length + 1;

  if (!vec3_buffer_push(buffer, VEC3(0, 0, 0)))
    return 0; // to make sure we have available space

  for (int i = right; i > start - 1; i--) {
    buffer->items[MIN(buffer->length - 1, i + 1)] = buffer->items[i];
  }

  buffer->items[start] = point;

  return 1;
}

int vec3_buffer_splice_remove(VEC3Buffer *buffer, int start, int64_t end) {
  VECTOR_BUFFER_GUARD(buffer);
  if (buffer->length <= 0 || buffer->items == 0)
    return 0;

  VEC3Buffer next_buffer = {0};
  vec3_buffer_init(&next_buffer);

  for (int64_t i = start; i < MIN(start + end, buffer->length - 1); i++) {
    Vector3 v = buffer->items[i % buffer->length];
    vec3_buffer_push(&next_buffer, v);
  }

  vec3_buffer_clear(buffer);
  *buffer = next_buffer;

  return 1;
}

int vec3_buffer_push_front(VEC3Buffer *buffer, Vector3 v) {
  VECTOR_BUFFER_GUARD(buffer);
  return vec3_buffer_splice(buffer, 0, v);
}

int vec3_array_translate(Vector3 *vectors, int64_t length, Vector3 pos,
                         VEC3Rotation rotation) {
  if (!vectors || !length)
    return 0;
  mat4 rot = GLM_MAT4_IDENTITY_INIT;
  // rotation.origin = VEC3(0, 0, 0);

  if (rotation.angle > 0 || fabsf(vector3_mag(rotation.value)) > 0) {
    vec3_matrix_generate(pos.x, pos.y, pos.z, rotation.value.x,
                         rotation.value.y, rotation.value.z, rotation.origin.x,
                         rotation.origin.y, rotation.origin.z, 0, rot,
                         rotation.order);
  }

  for (int64_t i = 0; i < length; i++) {
    Vector3 v = vectors[i];

    if (rotation.angle > 0 || fabsf(vector3_mag(rotation.value)) > 0) {

      v.u = 1;
      v.w = 1;
      v = vector3_project_onto_mat4(v, rot);

    } else {
      v = vector3_add(v, pos);
    }

    vectors[i] = v;
  }

  return 1;
}

Vector3Pair vec3_buffer_closest_points(VEC3Buffer a, VEC3Buffer b) {
  if (vec3_buffer_is_empty(a) || vec3_buffer_is_empty(b))
    return (Vector3Pair){VEC3(0, 0, 0), VEC3(0, 0, 0)};
  Vector3Pair pair = (Vector3Pair){.a = VEC3(0, 0, 0), .b = VEC3(0, 0, 0)};
  float min_dist = INFINITY;

  int64_t len = MAX(a.length, b.length);

  for (int64_t i = 0; i < len; i++) {
    Vector3 p1 = a.items[i % len];
    Vector3 p2 = b.items[i % len];

    float distance = (fabsf(vector3_mag(vector3_sub(p2, p1))) +
                      fabsf(glm_vec3_distance((vec3){p1.x, p1.y, p1.z},
                                              (vec3){p2.x, p2.y, p2.z}))) /
                     2.0f;

    if (distance < min_dist) {
      pair.a = p1;
      pair.b = p2;
      min_dist = distance;
    }
  }
  return pair;
}

Vector3Support vec3_buffer_furthest_closest_point_along_axis(VEC3Buffer a, Vector3 axis) {
  float max = -INFINITY;
  float min = INFINITY;
  Vector3 furthest = VEC3(0, 0, 0);
  Vector3 closest = VEC3(0, 0, 0);

  int64_t furthest_index = 0;
  int64_t closest_index = 0;

  for (int64_t i = 0; i < a.length; i++) {
    Vector3 v = a.items[i];
    float dot = vector3_dot(v, axis);
//    if (dot == 0) continue;

    if (dot > max) {
      max = dot;
      furthest = v;
      furthest_index = i;
    }

    if (dot < min) {
      closest = v;
      min = dot;
      closest_index = i;
    }
  }
  return (Vector3Support){ .furthest = furthest, .closest = closest, .furthest_index = furthest_index, .closest_index = closest_index };
}

Vector3Support vec3_buffer_furthest_closest_point_along_axis_with_remains(VEC3Buffer a, Vector3 axis, VEC3Buffer* remain_left, VEC3Buffer* remain_right) {
  if (!remain_left->initialized) {
    vec3_buffer_init(remain_left);
  }

  if (!remain_right->initialized) {
    vec3_buffer_init(remain_right);
  }

  Vector3Support support = vec3_buffer_furthest_closest_point_along_axis(a, axis);


  for (int64_t i = 0; i < a.length; i++) {
    Vector3 v = a.items[i];
    if (vector3_compare(v, support.closest) || vector3_compare(v, support.furthest)) continue;
    float dot = vector3_dot(v, axis);


    if (dot > 0) {
      vec3_buffer_push(remain_right, v);
    } else {
      vec3_buffer_push(remain_left, v);
    }

  }

  return support;
}

Vector3SupportPair vec3_buffer_find_support(
  VEC3Buffer a,
  VEC3Buffer b,Vector3 axis) {
  Vector3Support sa = vec3_buffer_furthest_closest_point_along_axis(a, axis);
  Vector3Support sb = vec3_buffer_furthest_closest_point_along_axis(b, vector3_scale(axis, -1));
  Vector3 p1 = sa.furthest;
  Vector3 p2 = sb.furthest;
  Vector3 point = vector3_sub(p1, p2);

  Vector3SupportPair pair = { .a =sa, .b = sb, .point = point };
  return pair;
}

VEC3Buffer vec3_buffer_get_by_indices(VEC3Buffer buffer, Int64Buffer indices) {
  if (vec3_buffer_is_empty(buffer) || !indices.length)
    return (VEC3Buffer){0};

  VEC3Buffer buf = {0};
  vec3_buffer_init(&buf);

  for (int64_t i = 0; i < indices.length; i++) {
    int64_t index = indices.data[i];
    Vector3 v = buffer.items[index % buffer.length];

    vec3_buffer_push(&buf, v);
  }

  return buf;
}

VEC3Buffer vec3_buffer_find_points_along_axis(VEC3Buffer a, Vector3 axis) {
  VEC3Buffer buff = {0};
  vec3_buffer_init(&buff);
  for (int64_t i = 0; i < a.length; i++) {
    Vector3 v = a.items[i];
    float dot = vector3_dot(v, axis);
    if (dot > 0) {
      vec3_buffer_push(&buff, v);
    }
  }

  return buff;
}

int64_t vec3_buffer_find_index_between(VEC3Buffer a, Vector3 p1, Vector3 p2) {
  if (a.length <= 0) return 0;

  Vector3Pair pair = vector3_min_max(p1, p2);


  int64_t count = 0;
  int64_t start = 0;
  unsigned int found_min = 0;
  for (int64_t i = 0; i < a.length; i++) {
    Vector3 v = a.items[i];

    if (vector3_compare(v, pair.a) && !found_min) {
      found_min = 1;
      start = i;
    } else if (found_min) {
      count += 1;
      if (vector3_compare(v, pair.b)) break;
    }
  }

  return start + (count / 2);
}

int vec3_buffer_shift_left(VEC3Buffer *array, int index) {
  if (!array || array->length <= 0) return 0;
  for (int i = index; i < array->length - 1; i++)
    array->items[i] = array->items[i + 1];

  return 1;
}

int vec3_buffer_shift_right(VEC3Buffer *array, int index) {
  if (!array || array->length <= 0) return 0;
  for (int i = array->length - 1; i >= index; i--) {
    array->items[MIN(array->length - 1, i + 1)] = array->items[i];
    array->items[i] = VEC3(0, 0, 0);
  }

  return 1;
}

int vec3_buffer_push_at(VEC3Buffer* a, Vector3 v, int64_t index) {
  if (!a) return 0;
  a->items =
    (Vector3 *)realloc(a->items, (a->length + 1) * sizeof(Vector3));

  a->length++;
  vec3_buffer_shift_right(a, index);

  a->items[index] = v;

  return 1;
}

int vec3_buffer_remove_by_index(VEC3Buffer* src, int64_t index) {
  if (!src || src->length <= 0) return 0;

  if (index < 0) return 0;

  vec3_buffer_shift_left(src, index);

  if (src->length-1 <= 0) {
    vec3_buffer_clear(src);
    return 1;
  }

  src->items = (Vector3*)realloc(src->items, (src->length-1) * sizeof(Vector3));
  src->length -= 1;

  return 1;
}

int vec3_buffer_remove(VEC3Buffer* src, Vector3 v) {
  if (!src || src->length <= 0) return 0;

  int64_t index = -1;
  for (int64_t i = 0; i < src->length; i++) {
    if (vector3_compare(src->items[i], v)) {
      index = i;
      break;
    }
  }

  if (index < 0) return 0;

  return vec3_buffer_remove_by_index(src, index);
}

int vec3_buffer_remove_matching(VEC3Buffer* src, VEC3Buffer lookup) {
  if (!src || src->length <= 0) return 0;
  if (vec3_buffer_is_empty(lookup)) return 0;



  for (int64_t j = 0; j < lookup.length; j++) {
    for (int64_t i = 0; i < src->length; i++) {
      if (vector3_compare(src->items[i], lookup.items[j])) {
        vec3_buffer_remove_by_index(src, i);
      }
    }
  }

  return 1;
}


int vec3_buffer_pop(VEC3Buffer* buffer) {
  if (buffer->length <= 0 || buffer->items == 0) return 0;

  if (buffer->length-1 <= 0) {
    vec3_buffer_clear(buffer);
    return 1;
  }

 // buffer->items[buffer->length-1] = 0;


  buffer->items = (Vector3*)realloc(buffer->items, (buffer->length-1) * sizeof(Vector3));
  buffer->length -= 1;
  return 1;
}
