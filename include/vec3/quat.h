#ifndef VEC3_QUAT_H
#define VEC3_QUAT_H
#include <vec3/vec3.h>
void vec3_quat_for_angular_velocity(Vector3 velocity, double dt, vec4 out);
void vec3_quat_forward_to_up(vec4 q);
#endif
