#ifndef VEC3_MATRIX_H
#define VEC3_MATRIX_H
#include <vec3/vec3.h>

typedef struct {
  Vector4 r1;
  Vector4 r2;
  Vector4 r3;
  Vector4 r4;
} VEC3Mat4;


typedef enum {
  GLE_ROTATION_ORDER_XYZ,
  GLE_ROTATION_ORDER_YXZ,
  GLE_ROTATION_ORDER_ZYX,
  GLE_ROTATION_ORDER_ZXY
} VEC3RotationOrder;

void vec3_matrix_generate(float trans_x, float trans_y, float trans_z, float rot_x,
                     float rot_y, float rot_z, float offset_x, float offset_y,
                     float offset_z, unsigned int reverse, mat4 final,
                     VEC3RotationOrder order);
#endif
