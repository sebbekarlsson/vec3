#include <vec3/vec3.h>

int main(int argc,  char* argv[]) {


  Vector3* vectors = (Vector3[]){
    VEC3(10, 20, 10),
    VEC3(5, 32, 1),
    VEC3(1, 2, 1),
    VEC3(100, 20, 60),
    VEC3(18, 2, 0)
};


  Vector3 min = vector3_find_min_vec(vectors, 5);
  Vector3 max = vector3_find_max_vec(vectors, 5);


  printf("Min:\n");
  VEC3_PRINT(min);
  printf("Max:\n");
  VEC3_PRINT(max);

  return 0;
}
