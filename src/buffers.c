#include <vec3/buffers.h>
#include <stdlib.h>
#include <stdio.h>

void int64_buffer_init(Int64Buffer* buffer) {
  if (buffer->initialized == 1) return;
  buffer->data = 0;
  buffer->length = 0;
  buffer->initialized = 1;
}

int int64_buffer_push(Int64Buffer* buffer, int64_t value) {
  if (!buffer->initialized) return 0;
  buffer->length++;
  buffer->data = (int64_t*)realloc(buffer->data, buffer->length * sizeof(int64_t));
  buffer->data[buffer->length-1] = value;

  return buffer->length > 0 && buffer->data != 0;
}

int int64_buffer_push_unique(Int64Buffer* buffer, int64_t value) {
  if (!buffer->initialized) return 0;

  if (!int64_buffer_includes(buffer, value)) {
    int64_buffer_push(buffer, value);
  }

  return 1;
}

unsigned int int64_buffer_includes(Int64Buffer* buffer, int64_t value) {
  if (!buffer) return 0;
  if (!buffer->initialized) return 0;
  if (!buffer->data) return 0;
  if (!buffer->length) return 0;

  for (int64_t i = 0; i < buffer->length; i++) {
    if (buffer->data[i] == value) return 1;
  }

  return 0;
}


void int64_buffer_clear(Int64Buffer* buffer) {
  if (buffer->data != 0) {
    free(buffer->data);
    buffer->data = 0;
  }
  buffer->length = 0;
}

void int64_buffer_print(Int64Buffer buffer) {
  printf("[");
  if (buffer.data != 0) {
    for (int64_t i = 0; i < buffer.length; i++) {
      printf("%ld", buffer.data[i]);

      if (i < buffer.length-1) {
        printf(", ");
      }

    }
  }
  printf("]\n");
}
