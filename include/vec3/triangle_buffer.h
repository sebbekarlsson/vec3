#ifndef VEC3_TRIANGLE_VEC3_TRIANGLE_BUFFER_H
#define VEC3_TRIANGLE_VEC3_TRIANGLE_BUFFER_H
#include <vec3/vec3.h>
#include <vec3/matrix.h>
#include <vec3/buffers.h>
#include <vec3/triangle.h>

typedef struct {
  VEC3Triangle* items;
  int64_t length;

  unsigned int initialized;
} VEC3TriangleBuffer;

void vec3_triangle_buffer_init(VEC3TriangleBuffer* buffer);

void vec3_triangle_buffer_deref(VEC3TriangleBuffer* buffer);

void vec3_triangle_buffer_never_generate_normals(VEC3TriangleBuffer* buffer);

int vec3_triangle_buffer_push(VEC3TriangleBuffer* buffer, VEC3Triangle v);

unsigned int vec3_triangle_buffer_is_empty(VEC3TriangleBuffer buffer);
int vec3_triangle_buffer_clear(VEC3TriangleBuffer* buffer);

int vec3_triangle_buffer_allocate(VEC3TriangleBuffer* buffer, int64_t n);

int vec3_triangle_buffer_translate(VEC3TriangleBuffer* buffer, VEC3Triangle pos, VEC3Rotation rotation);
int vec3_triangle_buffer_translate_copy(VEC3TriangleBuffer* dest, VEC3TriangleBuffer src, VEC3Triangle pos, VEC3Rotation rotation);


int vec3_triangle_buffer_pop(VEC3TriangleBuffer* buffer);
int vec3_triangle_buffer_pop_out(VEC3TriangleBuffer* buffer, VEC3Triangle* out);

VEC3Triangle vec3_triangle_buffer_back(VEC3TriangleBuffer buffer);

VEC3Triangle vec3_triangle_buffer_get(VEC3TriangleBuffer buffer, int64_t index);
int vec3_triangle_buffer_set(VEC3TriangleBuffer* buffer, int64_t index, VEC3Triangle v);


int vec3_triangle_buffer_push_at(VEC3TriangleBuffer* a, VEC3Triangle v, int64_t index);
int vec3_triangle_buffer_remove(VEC3TriangleBuffer* src, VEC3Triangle v);

int vec3_triangle_buffer_remove_by_index(VEC3TriangleBuffer* src, int64_t index);



#endif
