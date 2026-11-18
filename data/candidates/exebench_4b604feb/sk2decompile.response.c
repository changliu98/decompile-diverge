void ml_multiply_mat2_mat2(float *a, float *b, float *c) {
  float a0 = a[0] * b[0] + a[1] * b[2];
  float a1 = a[0] * b[1] + a[1] * b[3];
  float a2 = a[2] * b[0] + a[3] * b[2];
  float a3 = a[2] * b[1] + a[3] * b[3];
  c[0] = a0;
  c[1] = a1;
  c[2] = a2;
  c[3] = a3;
}