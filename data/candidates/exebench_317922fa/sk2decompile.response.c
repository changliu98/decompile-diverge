void fft2pt(float *a) {
  float a0, a1, a2, a3;
  a0 = a[0];
  a1 = a[1];
  a2 = a[2];
  a3 = a[3];
  a[0] = a0 + a2;
  a[1] = a1 + a3;
  a[2] = a0 - a2;
  a[3] = a1 - a3;
}