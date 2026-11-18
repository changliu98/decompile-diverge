void Mat4_vec3_mul_inv(float *dst, float *a, float *b) {
  float x = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] -
            (a[0] * a[12] + a[1] * a[13] + a[2] * a[14]);
  float y = a[4] * b[0] + a[5] * b[1] + a[6] * b[2] -
            (a[4] * a[12] + a[5] * a[13] + a[6] * a[14]);
  float z = a[8] * b[0] + a[9] * b[1] + a[10] * b[2] -
            (a[8] * a[12] + a[9] * a[13] + a[10] * a[14]);
  dst[0] = x;
  dst[1] = y;
  dst[2] = z;
}