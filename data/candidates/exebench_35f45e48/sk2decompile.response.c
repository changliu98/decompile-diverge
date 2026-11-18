void fft4pt(float *a) {
  float a0, a1, a2, a3, a4, a5, a6, a7;
  a0 = a[0];
  a1 = a[1];
  a2 = a[2];
  a3 = a[3];
  a4 = a[4];
  a5 = a[5];
  a6 = a[6];
  a7 = a[7];
  a0 += a4;
  a1 += a5;
  a4 = a0 - a4;
  a5 = a1 - a5;
  a2 -= a6;
  a3 -= a7;
  a6 += a2;
  a7 += a3;
  a[0] = a0 + a6;
  a[1] = a1 + a7;
  a[2] = a4 + a3;
  a[3] = a5 - a2;
  a[4] = a0 - a6;
  a[5] = a1 - a7;
  a[6] = a4 - a3;
  a[7] = a5 + a2;
}