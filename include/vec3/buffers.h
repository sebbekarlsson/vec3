#ifndef VEC3_BUFFERS_H
#define VEC3_BUFFERS_H
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  int64_t* data;
  int64_t length;
  unsigned int initialized;
} Int64Buffer;


void int64_buffer_init(Int64Buffer* buffer);
int int64_buffer_push(Int64Buffer* buffer, int64_t value);
int int64_buffer_push_unique(Int64Buffer* buffer, int64_t value);

unsigned int int64_buffer_includes(Int64Buffer* buffer, int64_t value);

void int64_buffer_clear(Int64Buffer* buffer);

void int64_buffer_print(Int64Buffer buffer);

#endif
