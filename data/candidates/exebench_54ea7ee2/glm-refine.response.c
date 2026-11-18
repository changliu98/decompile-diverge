void __cdecl BTIC2D_TransWHT_Vert8(int *iblk, int *oblk)
{
  int ib0, ib1, ib2, ib3, ib4, ib5, ib6, ib7;
  int a6, a7, b1, b3, b5, b7, c1, c2, c4;
  int s0, s1, s2, s3, s4, s5, s6, s7;

  // Load input block (stride 8)
  ib0 = iblk[0];
  ib1 = iblk[1];
  ib2 = iblk[2];
  ib3 = iblk[3];
  ib4 = iblk[4];
  ib5 = iblk[5];
  ib6 = iblk[6];
  ib7 = iblk[7];

  // Intermediate sums
  s0 = ib4 + ib0;
  s1 = ib6 + ib2;
  s2 = ib7 + ib3;
  s3 = ib5 + ib1;
  s4 = s1 + s0;
  s5 = s2 + s3;
  s6 = s5 + s4;
  s7 = s6 + ib4; // Equivalent to s5 + s1 + ib0

  // Stage A
  a6 = (s1 / 2) - ib6;
  a7 = (s2 / 2) - ib7;

  // Stage B
  b1 = s5;
  b3 = (b1 / 2) - s2;
  b5 = a7 + (s3 / 2) - ib5;
  b7 = (b5 / 2) - a7;

  // Stage C
  c1 = (s6 / 2) - b1;
  c2 = b3 + (s4 / 2) - s1;
  c4 = b5 + a6 + (s0 / 2) - ib4;

  // Write output block (stride 8)
  oblk[0] = s6;
  oblk[1] = c4;
  oblk[2] = b7 + ((a6 + (s0 / 2) - ib4) / 2) - a6;
  oblk[3] = c2;
  oblk[4] = (c2 / 2) - b3;
  oblk[5] = (b7 + ((a6 + (s0 / 2) - ib4) / 2) - a6) / 2 - b7;
  oblk[6] = (c4 / 2) - b5;
  oblk[7] = c1;
}