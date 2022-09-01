#ifndef VEC3_MATRIX_H
#define VEC3_MATRIX_H
#include <vec3/vec3.h>

typedef struct {
  mat4 value;
} VEC3Mat4;


typedef enum {
  VEC3_ROTATION_ORDER_XYZ,
  VEC3_ROTATION_ORDER_YXZ,
  VEC3_ROTATION_ORDER_ZYX,
  VEC3_ROTATION_ORDER_ZXY
} VEC3RotationOrder;

typedef struct {
  Vector3 value;
  Vector3 origin;
  float angle;
  VEC3RotationOrder order;
} VEC3Rotation;

void vec3_matrix_generate(float trans_x, float trans_y, float trans_z, float rot_x,
                     float rot_y, float rot_z, float offset_x, float offset_y,
                     float offset_z, unsigned int reverse, mat4 final,
                          VEC3RotationOrder order);


void vec3_mat4_print(mat4 v);
#endif
