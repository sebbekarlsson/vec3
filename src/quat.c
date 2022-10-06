#include <vec3/quat.h>


void vec3_quat_for_angular_velocity(Vector3 velocity, double dt, vec4 out) {
  Vector3 delta_rotation = vector3_scale(velocity, dt);
  float delta_theta = vector3_mag(delta_rotation);

  Vector3 rotation_norm = vector3_unit(delta_rotation);

  float s = sinf(delta_theta * 0.5f);
  float c = cosf(delta_theta * 0.5f);


  glm_quat_init(
    out,
    rotation_norm.x * s,
    rotation_norm.y * s,
    rotation_norm.z * s,
    c
  );
}


void vec3_quat_forward_to_up(vec4 q) {
  vec4 fwd2up;
  glm_quat(fwd2up, glm_rad(90.0f), -1, 0, 0);
  glm_quat_mul(q, fwd2up, q);
}
