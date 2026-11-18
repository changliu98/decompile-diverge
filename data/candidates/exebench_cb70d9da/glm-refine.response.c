void __cdecl BTIC2D_TransDCT_Vert(int *iblk, int *oblk)
{
  // Load input block coefficients (stride of 8)
  int ib0 = iblk[0];
  int ib1 = iblk[8];
  int ib2 = iblk[16];
  int ib3 = iblk[24];
  int ib4 = iblk[32];
  int ib5 = iblk[40];
  int ib6 = iblk[48];
  int ib7 = iblk[56];

  // Precompute common differences and sums
  int d0_7 = ib0 - ib7;
  int d1_6 = ib1 - ib6;
  int d2_5 = ib2 - ib5;
  int d3_4 = ib3 - ib4;

  int s0_7 = ib0 + ib7;
  int s1_6 = ib1 + ib6;
  int s2_5 = ib2 + ib5;
  int s3_4 = ib3 + ib4;

  // Intermediate stage calculations
  int ib0p7n3n4 = s0_7 - s3_4;
  int ib1p6n2n5 = s1_6 - s2_5;

  // Compute output coefficients with fixed-point scaling and rounding (+0x8000 >> 16)
  int ob0 = 91 * (s0_7 + s1_6 + s2_5 + s3_4);
  int ob1 = 126 * d0_7 + 106 * d1_6 + 71 * d2_5 + 25 * d3_4;
  int ob2 = 118 * ib0p7n3n4 + 49 * ib1p6n2n5;
  int ob3 = 106 * d0_7 - 25 * d1_6 - 126 * d2_5 - 71 * d3_4;
  int ob4 = 91 * (s0_7 + s3_4 - s1_6 - s2_5);
  int ob5 = 71 * d0_7 - 126 * d1_6 + 25 * d2_5 + 106 * d3_4;
  int ob6 = 49 * ib0p7n3n4 - 118 * ib1p6n2n5;
  int ob7 = 25 * d0_7 - 71 * d1_6 + 106 * d2_5 - 126 * d3_4;

  // Store output block coefficients with rounding
  oblk[0]  = (ob0 + 0x8000) >> 16;
  oblk[8]  = (ob1 + 0x8000) >> 16;
  oblk[16] = (ob2 + 0x8000) >> 16;
  oblk[24] = (ob3 + 0x8000) >> 16;
  oblk[32] = (ob4 + 0x8000) >> 16;
  oblk[40] = (ob5 + 0x8000) >> 16;
  oblk[48] = (ob6 + 0x8000) >> 16;
  oblk[56] = (ob7 + 0x8000) >> 16;
}