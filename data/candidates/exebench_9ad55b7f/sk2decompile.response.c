extern void warp_mat4_scale(float *result, const float *a, float s) {
  int i;
  for (i = 0; i < 16; i++) {
    result[i] = a[i] * s;
  }
}