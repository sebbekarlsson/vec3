#include <stdlib.h>
#include <string.h>
#include <vec3/macros.h>
#include <vec3/vector4_buffer.h>

void vec4_buffer_init(VEC4Buffer *buffer) {
  if (buffer->initialized)
    return;
  buffer->items = 0;
  buffer->length = 0;
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

int vec4_buffer_push(VEC4Buffer *buffer, Vector4 v) {
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items =
      (Vector4 *)realloc(buffer->items, (buffer->length + 1) * sizeof(Vector4));
  buffer->items[buffer->length] = v;
  buffer->length++;

  return buffer->length > 0 && buffer->items != 0;
}

int vec4_buffer_concat_vectors_front(VEC4Buffer *buffer, Vector4 *vectors,
                                     int64_t len) {
  if (!len || !vectors)
    return 0;
  VECTOR_BUFFER_GUARD(buffer);

  VEC4Buffer next_buffer = {0};
  vec4_buffer_init(&next_buffer);

  vec4_buffer_concat_vectors(&next_buffer, vectors, len);

  if (!vec4_buffer_is_empty(*buffer)) {
    vec4_buffer_concat_vectors(&next_buffer, buffer->items, buffer->length);
  }

  vec4_buffer_clear(buffer);

  *buffer = next_buffer;

  return buffer->length > 0 && buffer->items != 0;
}

int vec4_buffer_concat_vectors(VEC4Buffer *buffer, Vector4 *vectors,
                               int64_t len) {
  if (!len || !vectors)
    return 0;
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items = (Vector4 *)realloc(buffer->items,
                                     (buffer->length + len) * sizeof(Vector4));
  memcpy(&buffer->items[buffer->length], &vectors[0], len * sizeof(Vector4));
  buffer->length += len;

  return buffer->length > 0 && buffer->items != 0;
}


unsigned int vec4_buffer_is_empty(VEC4Buffer buffer) {
  return buffer.length <= 0 || buffer.items == 0;
}
int vec4_buffer_clear(VEC4Buffer *buffer) {
  VECTOR_BUFFER_GUARD(buffer);

  if (buffer->ref_count > 0)
    return 0;

  if (!vec4_buffer_is_empty(*buffer)) {
    free(buffer->items);
    buffer->items = 0;
    buffer->length = 0;
  }

  return 1;
}

int vec4_buffer_allocate(VEC4Buffer *buffer, int64_t n) {
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items =
      (Vector4 *)realloc(buffer->items, (buffer->length + n) * sizeof(Vector4));
  return buffer->items != 0;
}

int vec4_buffer_splice(VEC4Buffer *buffer, int start, Vector4 point) {
  VECTOR_BUFFER_GUARD(buffer);
  int right = buffer->length + 1;

  if (!vec4_buffer_push(buffer, VEC4(0, 0, 0, 0)))
    return 0; // to make sure we have available space

  for (int i = right; i > start - 1; i--) {
    buffer->items[MIN(buffer->length - 1, i + 1)] = buffer->items[i];
  }

  buffer->items[start] = point;

  return 1;
}

int vec4_buffer_splice_remove(VEC4Buffer *buffer, int start, int64_t end) {
  VECTOR_BUFFER_GUARD(buffer);
  if (buffer->length <= 0 || buffer->items == 0)
    return 0;

  VEC4Buffer next_buffer = {0};
  vec4_buffer_init(&next_buffer);

  for (int64_t i = start; i < MIN(start + end, buffer->length - 1); i++) {
    Vector4 v = buffer->items[i % buffer->length];
    vec4_buffer_push(&next_buffer, v);
  }

  vec4_buffer_clear(buffer);
  *buffer = next_buffer;

  return 1;
}

int vec4_buffer_push_front(VEC4Buffer *buffer, Vector4 v) {
  VECTOR_BUFFER_GUARD(buffer);
  return vec4_buffer_splice(buffer, 0, v);
}

VEC4Buffer vec4_buffer_get_by_indices(VEC4Buffer buffer, Int64Buffer indices) {
  if (vec4_buffer_is_empty(buffer) || !indices.length)
    return (VEC4Buffer){0};

  VEC4Buffer buf = {0};
  vec4_buffer_init(&buf);

  for (int64_t i = 0; i < indices.length; i++) {
    int64_t index = indices.data[i];
    Vector4 v = buffer.items[index % buffer.length];

    vec4_buffer_push(&buf, v);
  }

  return buf;
}

int vec4_buffer_shift_left(VEC4Buffer *array, int index) {
  if (!array || array->length <= 0) return 0;
  for (int i = index; i < array->length - 1; i++)
    array->items[i] = array->items[i + 1];

  return 1;
}

int vec4_buffer_shift_right(VEC4Buffer *array, int index) {
  if (!array || array->length <= 0) return 0;
  for (int i = array->length - 1; i >= index; i--) {
    array->items[MIN(array->length - 1, i + 1)] = array->items[i];
    array->items[i] = VEC4(0, 0, 0, 0);
  }

  return 1;
}

int vec4_buffer_push_at(VEC4Buffer* a, Vector4 v, int64_t index) {
  if (!a) return 0;
  a->items =
    (Vector4 *)realloc(a->items, (a->length + 1) * sizeof(Vector4));

  a->length++;
  vec4_buffer_shift_right(a, index);

  a->items[index] = v;

  return 1;
}

int vec4_buffer_remove_by_index(VEC4Buffer* src, int64_t index) {
  if (!src || src->length <= 0) return 0;

  if (index < 0) return 0;

  vec4_buffer_shift_left(src, index);

  if (src->length-1 <= 0) {
    vec4_buffer_clear(src);
    return 1;
  }

  src->items = (Vector4*)realloc(src->items, (src->length-1) * sizeof(Vector4));
  src->length -= 1;

  return 1;
}



int vec4_buffer_pop(VEC4Buffer* buffer) {
  if (buffer->length <= 0 || buffer->items == 0) return 0;

  if (buffer->length-1 <= 0) {
    vec4_buffer_clear(buffer);
    return 1;
  }

 // buffer->items[buffer->length-1] = 0;


  buffer->items = (Vector4*)realloc(buffer->items, (buffer->length-1) * sizeof(Vector4));
  buffer->length -= 1;
  return 1;
}
