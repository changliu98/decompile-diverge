void ml_multiply_mat4_vec4(float *a, float *b, float *c) {
  float x = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
  float y = a[4] * b[0] + a[5] * b[1] + a[6] * b[2] + a[7] * b[3];
  float z = a[8] * b[0] + a[9] * b[1] + a[10] * b[2] + a[11] * b[3];
  float w = a[12] * b[0] + a[13] * b[1] + a[14] * b[2] + a[15] * b[3];
  c[0] = x;
  c[1] = y;
  c[2] = z;
  c[3] = w;
}