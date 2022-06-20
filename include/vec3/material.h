#ifndef VEC3_MATERIAL_H
#define VEC3_MATERIAL_H
#include <vec3/vec3.h>
typedef struct {
  Vector4 base_color_factor;
  float roughness;
} VEC3Material;
#endif
