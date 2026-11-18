void cftf040(float *a) {
  float a0p4, a1p5, a2m3, a3m2, a4p6, a5p7, a6m5, a7m6;
  a0p4 = a[0] + a[4];
  a1p5 = a[1] + a[5];
  a2m3 = a[0] - a[4];
  a3m2 = a[1] - a[5];
  a4p6 = a[2] + a[6];
  a5p7 = a[3] + a[7];
  a6m5 = a[2] - a[6];
  a7m6 = a[3] - a[7];
  a[0] = a0p4 + a4p6;
  a[1] = a1p5 + a5p7;
  a[2] = a2m3 - a7m6;
  a[3] = a3m2 + a6m5;
  a[4] = a0p4 - a4p6;
  a[5] = a1p5 - a5p7;
  a[6] = a2m3 + a7m6;
  a[7] = a3m2 - a6m5;
}