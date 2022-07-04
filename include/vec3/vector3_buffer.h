#ifndef VEC3_VEC3_BUFFER_H
#define VEC3_VEC3_BUFFER_H
#include <vec3/vec3.h>
#include <vec3/matrix.h>
#include <vec3/buffers.h>

typedef struct {
  Vector3* items;
  int64_t length;

  Vector3* normals;
  int64_t normals_length;

  unsigned int never_generate_normals;

  unsigned int initialized;

  int ref_count;
} VEC3Buffer;

#define AS_VECTOR_BUFFER(vecs, len) ((VEC3Buffer){ .initialized = 1, .items = vecs, .length = len, .normals = 0, .normals_length = 0 })

void vec3_buffer_init(VEC3Buffer* buffer);

void vec3_buffer_deref(VEC3Buffer* buffer);

void vec3_buffer_never_generate_normals(VEC3Buffer* buffer);

int vec3_buffer_push(VEC3Buffer* buffer, Vector3 v);

int vec3_buffer_push_front(VEC3Buffer* buffer, Vector3 v);

int vec3_buffer_concat_vectors(VEC3Buffer* buffer, Vector3* vectors, int64_t len);

int vec3_buffer_concat_vectors_front(VEC3Buffer* buffer, Vector3* vectors,
                                     int64_t len);


unsigned int vec3_buffer_is_empty(VEC3Buffer buffer);
int vec3_buffer_clear(VEC3Buffer* buffer);

int vec3_buffer_allocate(VEC3Buffer* buffer, int64_t n);

Vector3* vec3_buffer_get_normals(VEC3Buffer* buffer, int64_t* len);

int vec3_buffer_generate_normals(VEC3Buffer* buffer);

int vec3_buffer_translate(VEC3Buffer* buffer, Vector3 pos, VEC3Rotation rotation);
int vec3_buffer_translate_copy(VEC3Buffer* dest, VEC3Buffer src, Vector3 pos, VEC3Rotation rotation);

int vec3_buffer_splice(VEC3Buffer* buffer, int start, Vector3 point);

int vec3_buffer_pop(VEC3Buffer* buffer);

Vector3 vec3_buffer_back(VEC3Buffer buffer);

Vector3 vec3_buffer_get(VEC3Buffer buffer, int64_t index);
int vec3_buffer_set(VEC3Buffer* buffer, int64_t index, Vector3 v);

int vec3_buffer_splice_remove(VEC3Buffer* buffer, int start,
                                    int64_t end);



Vector3Pair vec3_buffer_closest_points(VEC3Buffer a, VEC3Buffer b);


VEC3Buffer vec3_buffer_get_by_indices(VEC3Buffer buffer, Int64Buffer indices);

int vec3_array_translate(Vector3* vectors, int64_t length, Vector3 pos, VEC3Rotation rotation);

Vector3Support vec3_buffer_furthest_closest_point_along_axis(VEC3Buffer a, Vector3 axis);
Vector3SupportPair vec3_buffer_find_support(
  VEC3Buffer a,
  VEC3Buffer b,Vector3 axis);

#endif
