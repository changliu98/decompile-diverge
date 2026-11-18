void cftb040(float *a) {
  float a0p4, a1p5, a0m4, a1m5, a2p6, a3p7, a2m6, a3m7;
  a0p4 = a[0] + a[4];
  a1p5 = a[1] + a[5];
  a0m4 = a[0] - a[4];
  a1m5 = a[1] - a[5];
  a2p6 = a[2] + a[6];
  a3p7 = a[3] + a[7];
  a2m6 = a[2] - a[6];
  a3m7 = a[3] - a[7];
  a[0] = a0p4 + a2p6;
  a[1] = a1p5 + a3p7;
  a[2] = a0m4 + a3m7;
  a[3] = a1m5 - a2m6;
  a[4] = a0p4 - a2p6;
  a[5] = a1p5 - a3p7;
  a[6] = a0m4 - a3m7;
  a[7] = a1m5 + a2m6;
}