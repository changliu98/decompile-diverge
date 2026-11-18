void fft4pt(float *a) {
  float a0, a1, a2, a3, a4, a5, a6, a7;
  a0 = a[0];
  a1 = a[1];
  a2 = a[4];
  a3 = a[5];
  a4 = a[2];
  a5 = a[3];
  a6 = a[6];
  a7 = a[7];
  a0 += a2;
  a1 += a3;
  a2 = a0 - a2;
  a3 = a1 - a3;
  a4 -= a6;
  a5 -= a7;
  a6 += a4;
  a7 += a5;
  a[0] = a0 + a6;
  a[1] = a1 + a7;
  a[2] = a2 + a5;
  a[3] = a3 - a4;
  a[4] = a0 - a6;
  a[5] = a1 - a7;
  a[6] = a2 - a5;
  a[7] = a3 + a4;
}