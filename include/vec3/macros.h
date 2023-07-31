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


#define VEC3_CLI_RED "\x1B[31m"
#define VEC3_CLI_GREEN "\x1B[32m"
#define VEC3_CLI_YELLLOW "\x1B[33m"
#define VEC3_CLI_BLUE "\x1B[34m"
#define VEC3_CLI_MAGENTA "\x1B[35m"
#define VEC3_CLI_CYAN "\x1B[36m"
#define VEC3_CLI_WHITE "\x1B[37m"
#define VEC3_CLI_RESET "\x1B[0m"

#define VEC3_WARNING(...)                                                       \
  {                                                                            \
    printf(VEC3_CLI_RED "(VEC3)(Warning)(%s:%d): \n" VEC3_CLI_RESET, __func__,    \
           __LINE__);                                                          \
    fprintf(__VA_ARGS__);                                                      \
  }


#define VEC3_ASSERT_RETURN(expr, ret)                                           \
  {                                                                            \
    if (!(expr)) {                                                             \
      VEC3_WARNING(stderr, "(VEC3): Assertion failed: %s.\n", #expr);            \
      return ret;                                                              \
    }                                                                          \
  }
#endif
