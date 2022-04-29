#ifndef VEC3_BUFFERS_H
#define VEC3_BUFFERS_H
#include <stdint.h>

typedef struct {
  int64_t* data;
  int64_t length;
  unsigned int initialized;
} Int64Buffer;


void int64_buffer_init(Int64Buffer* buffer);
int int64_buffer_push(Int64Buffer* buffer, int64_t value);

unsigned int int64_buffer_includes(Int64Buffer* buffer, int64_t value);

#endif
