#include <vec3/batch.h>
#include <vec3/macros.h>
#include <vec3/vec3.h>

static bool vec3_batch_has_data(Vector3Batch b) {
  return b.length > 0 && b.items != 0;
}

static bool float_batch_has_data(Vector3FloatBatch b) {
  return b.length > 0 && b.items != 0;
}

#define VEC3_BATCH_HAS_DATA_GEN(T)                                         \
  _Generic((T), Vector3Batch                                                   \
           : vec3_batch_has_data, Vector3FloatBatch                            \
           : float_batch_has_data)

#define VEC3_BATCH_HAS_DATA(T)                  \
  VEC3_BATCH_HAS_DATA_GEN(T)(T)

#define VEC3_BATCH_CHECK_AB_OUT(BATCH_A, BATCH_B, OUT)                         \
  VEC3_ASSERT_RETURN(VEC3_BATCH_HAS_DATA(BATCH_A), OUT);                          \
  VEC3_ASSERT_RETURN(VEC3_BATCH_HAS_DATA(BATCH_B), OUT);                          \
  VEC3_ASSERT_RETURN(VEC3_BATCH_HAS_DATA(OUT), OUT);                           \
  VEC3_ASSERT_RETURN(BATCH_A.length == BATCH_B.length, OUT);                      \
  VEC3_ASSERT_RETURN(OUT.length == BATCH_A.length, OUT);

#define VEC3_BATCH_CHECK_A_OUT(BATCH_A, OUT)                                   \
  VEC3_ASSERT_RETURN(VEC3_BATCH_HAS_DATA(BATCH_A), OUT);                          \
  VEC3_ASSERT_RETURN(VEC3_BATCH_HAS_DATA(OUT), OUT);                           \
  VEC3_ASSERT_RETURN(OUT.length == BATCH_A.length, OUT);

#define VEC3_BATCH_OP_AB_OUT(BATCH_A, BATCH_B, OUT, BODY)                      \
  {                                                                            \
    VEC3_BATCH_CHECK_AB_OUT(BATCH_A, BATCH_B, OUT)                             \
    int64_t count = BATCH_A.length;                                            \
    for (int64_t i = 0; i < count; i++) {                                      \
      Vector3 a = BATCH_A.items[i];                                            \
      Vector3 b = BATCH_B.items[i];                                            \
      BODY                                                                     \
    }                                                                          \
  }

#define VEC3_BATCH_OP_AB_SCALAR_OUT(BATCH_A, BATCH_B, OUT, BODY)               \
  {                                                                            \
    VEC3_BATCH_CHECK_AB_OUT(BATCH_A, BATCH_B, OUT)                             \
    int64_t count = BATCH_A.length;                                            \
    for (int64_t i = 0; i < count; i++) {                                      \
      Vector3 a = BATCH_A.items[i];                                            \
      float b = BATCH_B.items[i];                                              \
      BODY                                                                     \
    }                                                                          \
  }

#define VEC3_BATCH_OP_A_OUT(BATCH_A, OUT, BODY)                                \
  {                                                                            \
    VEC3_BATCH_CHECK_A_OUT(BATCH_A, OUT)                                       \
    int64_t count = BATCH_A.length;                                            \
    for (int64_t i = 0; i < count; i++) {                                      \
      Vector3 a = vecs_a.items[i];                                             \
      BODY                                                                     \
    }                                                                          \
  }

Vector3Batch vector3_batch_add(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out) {
  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out,
                       { out.items[i] = vector3_add(a, b); });
  return out;
}

Vector3Batch vector3_batch_sub(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out) {
  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out,
                       { out.items[i] = vector3_sub(a, b); });
  return out;
}

Vector3Batch vector3_batch_mul(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out) {
  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out,
                       { out.items[i] = vector3_mul(a, b); });
  return out;
}

Vector3Batch vector3_batch_div(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3Batch out) {
  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out,
                       { out.items[i] = vector3_div(a, b); });
  return out;
}

Vector3Batch vector3_batch_cross(Vector3Batch vecs_a, Vector3Batch vecs_b,
                         Vector3Batch out) {
  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out,
                       { out.items[i] = vector3_cross(a, b); });
  return out;
}

Vector3Batch vector3_batch_unit(Vector3Batch vecs_a, Vector3Batch out) {
  VEC3_BATCH_OP_A_OUT(vecs_a, out, { out.items[i] = vector3_unit(a); });
  return out;
}

Vector3Batch vector3_batch_scale(Vector3Batch vecs_a, Vector3FloatBatch scales,
                         Vector3Batch out) {
  VEC3_BATCH_OP_AB_SCALAR_OUT(vecs_a, scales, out, {
    out.items[i] = vector3_scale(a, b);
  });

  return out;
}

Vector3FloatBatch vector3_batch_dot(Vector3Batch vecs_a, Vector3Batch vecs_b,
                       Vector3FloatBatch out) {

  VEC3_BATCH_OP_AB_OUT(vecs_a, vecs_b, out, { out.items[i] = vector3_dot(a, b); });

  return out;
}

void vector3_batch_print(Vector3Batch vecs, int columns, int precision, FILE* fp) {
  if (vecs.items == 0 || vecs.length <= 0 || fp == 0)
    return;

  columns = columns > 0 ? columns : 1;

  const char *fmt = 0;

  switch (precision) {
  case 0:
    fmt = "(%1.0f, %1.0f, %1.0f)";
    break;
  case 1:
    fmt = "(%1.1f, %1.1f, %1.1f)";
    break;
  case 2:
    fmt = "(%1.2f, %1.2f, %1.2f)";
    break;
  case 3:
    fmt = "(%1.3f, %1.3f, %1.3f)";
    break;
  case 4:
    fmt = "(%1.4f, %1.4f, %1.4f)";
    break;
  case 5:
    fmt = "(%1.5f, %1.5f, %1.5f)";
    break;
  default:
  case 6:
    fmt = "(%1.6f, %1.6f, %1.6f)";
    break;
  }

  // should never happen.
  if (fmt == 0) {
    fprintf(fp, "format string is NULL.\n");
  }

  for (int64_t i = 0; i < vecs.length; i++) {
    Vector3 v = vecs.items[i];
    fprintf(fp, fmt, v.x, v.y, v.z);

    if ((i + 1) % columns == 0) {
      fprintf(fp, "\n");
    } else if (i < vecs.length - 1) {
      fprintf(fp, " ");
    }
  }

  if (vecs.length % columns != 0) {
    fprintf(fp, "\n");
  }
}
