void crecip(limb *out, const limb *z) {
  limb z2[10], z9[10], z11[10], z11_5_0[10], z11_10_0[10], z11_2_1[10],
      z11_2_2[10], z11_2_3[10], z11_2_4[10], z11_2_5[10];
  int i;
  fsquare(z2, z);
  fsquare(z9, z2);
  fsquare(z11, z9);
  fmul(z11_2_1, z11, z);
  fmul(z11_2_2, z11_2_1, z2);
  fsquare(z11, z11_2_2);
  fmul(z11_2_3, z11, z11_2_1);
  fsquare(z11, z11_2_3);
  fsquare(z9, z11);
  fsquare(z11, z9);
  fsquare(z9, z11);
  fsquare(z11, z9);
  fmul(z11_2_4, z11, z11_2_3);
  fsquare(z11, z11_2_4);
  fsquare(z9, z11);
  for (i = 2; i < 10; i += 2) {
    fsquare(z11, z9);
    fsquare(z9, z11);
  }
  fmul(z11_2_5, z9, z11_2_4);
  fsquare(z11, z11_2_5);
  fsquare(z9, z11);
  for (i = 2; i < 20; i += 2) {
    fsquare(z11, z9);
    fsquare(z9, z11);
  }
  fmul(z11, z9, z11_2_5);
  fsquare(z9, z11);
  fsquare(z11, z9);
  for (i = 2; i < 10; i += 2) {
    fsquare(z9, z11);
    fsquare(z11, z9);
  }
  fmul(z11_5_0, z11, z11_2_4);
  fsquare(z11, z11_5_0);
  fsquare(z9, z11);
  for (i = 2; i < 50; i += 2) {
    fsquare(z11, z9);
    fsquare(z9, z11);
  }
  fmul(z11_10_0, z9, z11_5_0);
  fsquare(z9, z11_10_0);
  fsquare(z11, z9);
  for (i = 2; i < 100; i += 2) {
    fsquare(z9, z11);
    fsquare(z11, z9);
  }
  fmul(z11, z9, z11_10_0);
  fsquare(z9, z11);
  fsquare(z11, z9);
  for (i = 2; i < 50; i += 2) {
    fsquare(z11, z9);
    fsquare(z9, z11);
  }
  fmul(z9, z11, z11_5_0);
  fsquare(z11, z9);
  fsquare(z9, z11);
  fsquare(z11, z9);
  fsquare(z9, z11);
  fsquare(z11, z9);
  fmul(out, z11, z11_2_2);
}