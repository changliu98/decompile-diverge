void xformMultiply(float *a, float *b) {
  float a0, a2, a4;
  float a1, a3, a5;
  a0 = a[0] * b[0] + a[1] * b[2];
  a2 = a[2] * b[0] + a[3] * b[2];
  a4 = a[4] * b[0] + a[5] * b[2] + b[4];
  a1 = a[0] * b[1] + a[1] * b[3];
  a3 = a[2] * b[1] + a[3] * b[3];
  a5 = a[4] * b[1] + a[5] * b[3] + b[5];
  a[1] = a1;
  a[3] = a3;
  a[5] = a5;
  a[0] = a0;
  a[2] = a2;
  a[4] = a4;
}