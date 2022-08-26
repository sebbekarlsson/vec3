#ifndef VEC4_VEC4_BUFFER_H
#define VEC4_VEC4_BUFFER_H
#include <vec3/vec3.h>
#include <vec3/matrix.h>
#include <vec3/buffers.h>

typedef struct {
  Vector4* items;
  int64_t length;

  unsigned int initialized;

  int ref_count;
} VEC4Buffer;

#define AS_VEC4_BUFFER(vecs, len) ((VEC4Buffer){ .initialized = 1, .items = vecs, .length = len })

void vec4_buffer_init(VEC4Buffer* buffer);

void vec4_buffer_deref(VEC4Buffer* buffer);


int vec4_buffer_push(VEC4Buffer* buffer, Vector4 v);

int vec4_buffer_push_front(VEC4Buffer* buffer, Vector4 v);

int vec4_buffer_concat_vectors(VEC4Buffer* buffer, Vector4* vectors, int64_t len);

int vec4_buffer_concat_vectors_front(VEC4Buffer* buffer, Vector4* vectors,
                                     int64_t len);


unsigned int vec4_buffer_is_empty(VEC4Buffer buffer);
int vec4_buffer_clear(VEC4Buffer* buffer);

int vec4_buffer_allocate(VEC4Buffer* buffer, int64_t n);

int vec4_buffer_splice(VEC4Buffer* buffer, int start, Vector4 point);

int vec4_buffer_pop(VEC4Buffer* buffer);

Vector4 vec4_buffer_back(VEC4Buffer buffer);

Vector4 vec4_buffer_get(VEC4Buffer buffer, int64_t index);
int vec4_buffer_set(VEC4Buffer* buffer, int64_t index, Vector4 v);

int vec4_buffer_splice_remove(VEC4Buffer* buffer, int start,
                                    int64_t end);



VEC4Buffer vec4_buffer_get_by_indices(VEC4Buffer buffer, Int64Buffer indices);




int vec4_buffer_push_at(VEC4Buffer* a, Vector4 v, int64_t index);


#endif
