#include <stdlib.h>
#include <string.h>
#include <vec3/macros.h>
#include <vec3/triangle_buffer.h>

void vec3_triangle_buffer_init(VEC3TriangleBuffer *buffer) {
  if (buffer->initialized)
    return;
  buffer->items = 0;
  buffer->length = 0;
  buffer->initialized = 1;
}

#define VECTOR_BUFFER_GUARD(buffer)                                            \
  {                                                                            \
    if (!buffer->initialized) {                                                \
      fprintf(stderr, "This vector buffer is not initialized! (%s)\n",         \
              __func__);                                                       \
    }                                                                          \
  }

int vec3_triangle_buffer_push(VEC3TriangleBuffer *buffer, VEC3Triangle v) {
  VECTOR_BUFFER_GUARD(buffer);
  buffer->items =
      (VEC3Triangle *)realloc(buffer->items, (buffer->length + 1) * sizeof(VEC3Triangle));
  buffer->items[buffer->length] = v;
  buffer->length++;

  return buffer->length > 0 && buffer->items != 0;
}

unsigned int vec3_triangle_buffer_is_empty(VEC3TriangleBuffer buffer) {
  return buffer.length <= 0 || buffer.items == 0;
}
int vec3_triangle_buffer_clear(VEC3TriangleBuffer *buffer) {
  VECTOR_BUFFER_GUARD(buffer);


  if (buffer->items != 0) {
    free(buffer->items);
  }
  buffer->items = 0;
  buffer->length = 0;

  return 1;
}


int vec3_triangle_buffer_shift_left(VEC3TriangleBuffer *array, int64_t index) {
  if (!array || array->length <= 0) return 0;
  for (int64_t i = index; i < array->length - 1; i++)
    array->items[i] = array->items[i + 1];

  return 1;
}

int vec3_triangle_buffer_shift_right(VEC3TriangleBuffer *array, int64_t index) {
  if (!array || array->length <= 0) return 0;
  for (int64_t i = array->length - 1; i >= index; i--) {
    array->items[MIN(array->length - 1, i + 1)] = array->items[i];
    array->items[i] = (VEC3Triangle){0};
  }

  return 1;
}

int vec3_triangle_buffer_push_at(VEC3TriangleBuffer* a, VEC3Triangle v, int64_t index) {
  if (!a) return 0;
  if (index < 0 || index >= a->length) return 0;
  a->items =
    (VEC3Triangle *)realloc(a->items, (a->length + 1) * sizeof(VEC3Triangle));

  a->length++;
  vec3_triangle_buffer_shift_right(a, index);

  a->items[index] = v;

  return 1;
}

int vec3_triangle_buffer_remove_by_index(VEC3TriangleBuffer* src, int64_t index) {
  if (!src || src->length <= 0) return 0;

  if (index < 0) return 0;

  vec3_triangle_buffer_shift_left(src, index);

  if (src->length-1 <= 0) {
    vec3_triangle_buffer_clear(src);
    return 1;
  }

  src->items = (VEC3Triangle*)realloc(src->items, (src->length-1) * sizeof(VEC3Triangle));
  src->length -= 1;

  return 1;
}


int vec3_triangle_buffer_pop(VEC3TriangleBuffer* buffer) {
  if (buffer->length <= 0 || buffer->items == 0) return 0;

  if (buffer->length-1 <= 0) {
    vec3_triangle_buffer_clear(buffer);
    return 1;
  }

 // buffer->items[buffer->length-1] = 0;


  buffer->items = (VEC3Triangle*)realloc(buffer->items, (buffer->length-1) * sizeof(VEC3Triangle));
  buffer->length -= 1;
  return 1;
}


int vec3_triangle_buffer_pop_out(VEC3TriangleBuffer* buffer, VEC3Triangle* out) {
    if (buffer->length <= 0 || buffer->items == 0 || !out) return 0;

    if (buffer->length-1 <= 0) {
    VEC3Triangle tri = buffer->items[0];
    vec3_triangle_buffer_clear(buffer);
    *out = tri;
    return 1;
  }

 // buffer->items[buffer->length-1] = 0;

    VEC3Triangle tri = buffer->items[MAX(0, buffer->length-1)];

  buffer->items = (VEC3Triangle*)realloc(buffer->items, (buffer->length-1) * sizeof(VEC3Triangle));
  buffer->length -= 1;

  *out = tri;

  return 1;
}
