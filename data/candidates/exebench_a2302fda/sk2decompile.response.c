static void mdct_butterfly_8(float *x) {
  float a0, a1, a2, a3, a4, a5;
  a0 = x[6] + x[2];
  a1 = x[6] - x[2];
  a2 = x[4] + x[0];
  a3 = x[4] - x[0];
  x[6] = a0 + a2;
  x[4] = a0 - a2;
  a4 = x[5] - x[1];
  a5 = x[7] - x[3];
  x[0] = a1 + a4;
  x[2] = a1 - a4;
  a4 = x[5] + x[1];
  a5 = x[7] + x[3];
  x[3] = a5 + a3;
  x[1] = a5 - a3;
  x[7] = a4 + a2;
  x[5] = a4 - a2;
}