#ifndef VEC3_MACROS_H
#define VEC3_MACROS_H
#include <stdlib.h>
#define NEW(T) ((T *)calloc(1, sizeof(T)))
#define LIST_ARGS(T, name) T name[], uint32_t name_length
#define OR(a, b) a ? a : b
#define MAYBE_STRDUP(v) (v == 0 ? 0 : strdup(v))
#define IS_FALSE(v) (v <= 0)
#define IS_TRUE(v) (v >= 1)



#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif
#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif


#endif
