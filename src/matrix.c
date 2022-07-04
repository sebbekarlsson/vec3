#include <vec3/matrix.h>


void vec3_matrix_generate(float trans_x, float trans_y, float trans_z, float rot_x,
                     float rot_y, float rot_z, float offset_x, float offset_y,
                     float offset_z, unsigned int reverse, mat4 final,
                      VEC3RotationOrder order) {





  vec4 qx = GLM_QUAT_IDENTITY_INIT;
  vec4 qy = GLM_QUAT_IDENTITY_INIT;
  vec4 qz = GLM_QUAT_IDENTITY_INIT;


  glm_quat(qx, glm_rad(rot_x), 1.0f, 0.0f, 0.0f);
  glm_quat(qy, glm_rad(rot_y), 0.0f, 1.0f, 0.0f);
  glm_quat(qz, glm_rad(rot_z), 0.0f, 0.0f, 1.0f);


  mat4 trans = GLM_MAT4_IDENTITY_INIT;
  mat4 trans_two = GLM_MAT4_IDENTITY_INIT;
  mat4 trans_pos = GLM_MAT4_IDENTITY_INIT;
  mat4 rot = GLM_MAT4_IDENTITY_INIT;

  switch (order) {
    case VEC3_ROTATION_ORDER_YXZ:
      glm_quat_rotate_at(rot, qy, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qx, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qz, (vec3){offset_x, offset_y, offset_z});
      break;
    case VEC3_ROTATION_ORDER_ZXY:
      glm_quat_rotate_at(rot, qz, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qx, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qy, (vec3){offset_x, offset_y, offset_z});
      break;
    case VEC3_ROTATION_ORDER_XYZ:
    case VEC3_ROTATION_ORDER_ZYX:
    default:
      glm_quat_rotate_at(rot, qx, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qy, (vec3){offset_x, offset_y, offset_z});
      glm_quat_rotate_at(rot, qz, (vec3){offset_x, offset_y, offset_z});
      break;
    }


  offset_x = 0;
  offset_y = 0;
  offset_z = 0;

  if (!reverse) {
    glm_translate(trans, (vec3){trans_x + offset_x, trans_y + offset_y,
                                trans_z + offset_z});
    glm_translate(trans_two,
                  (vec3){-(trans_x + offset_x), -(trans_y + offset_y),
                         -(trans_z + offset_z)});
  } else {
    glm_translate(trans_two, (vec3){trans_x + offset_x, trans_y + offset_y,
                                    trans_z + offset_z});
    glm_translate(trans, (vec3){-(trans_x + offset_x), -(trans_y + offset_y),
                                -(trans_z + offset_z)});
  }

  glm_translate(trans_pos, (vec3){trans_x, trans_y, trans_z});

  glm_mat4_mulN((mat4 *[]){&trans, &rot, &trans_two, &trans_pos}, 4, final);
}
