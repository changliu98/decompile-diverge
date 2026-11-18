void __cdecl crecip(limb *out, const limb *z)
{
  int j;
  limb t1[10];
  limb t0[10];
  limb z2_100_0[10];
  limb z2_50_0[10];
  limb z2_20_0[10];
  limb z2_10_0[10];
  limb z2_5_0[10];
  limb z11[10];
  limb z9[10];
  limb z2[10];

  // z2 = z^2
  fsquare(z2, z);
  
  // t1 = z^4
  fsquare(t1, z2);
  
  // t0 = z^8
  fsquare(t0, t1);
  
  // z9 = z^9
  fmul(z9, t0, z);
  
  // z11 = z^11
  fmul(z11, z9, z2);
  
  // t0 = z^22
  fsquare(t0, z11);
  
  // z2_5_0 = z^31
  fmul(z2_5_0, t0, z9);

  // t0 = z^(31 * 2^5) = z^992
  fsquare(t0, z2_5_0);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  fsquare(t0, t1);
  
  // z2_10_0 = z^1023
  fmul(z2_10_0, t0, z2_5_0);

  // t1 = z^(1023 * 2^10) = z^1047552
  fsquare(t0, z2_10_0);
  fsquare(t1, t0);
  for ( j = 2; j < 10; j += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  
  // z2_20_0 = z^1048575
  fmul(z2_20_0, t1, z2_10_0);

  // t1 = z^(1048575 * 2^20) = z^1099511627775
  fsquare(t0, z2_20_0);
  fsquare(t1, t0);
  for ( j = 2; j < 20; j += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  
  // t0 = z^1103806595327
  fmul(t0, t1, z2_20_0);
  
  // t0 = z^(1103806595327 * 2^10) = z^1129075050854400
  fsquare(t1, t0);
  fsquare(t0, t1);
  for ( j = 2; j < 10; j += 2 )
  {
    fsquare(t1, t0);
    fsquare(t0, t1);
  }
  
  // z2_50_0 = z^1129243895911423
  fmul(z2_50_0, t0, z2_10_0);

  // t1 = z^(1129243895911423 * 2^50)
  fsquare(t0, z2_50_0);
  fsquare(t1, t0);
  for ( j = 2; j < 50; j += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  
  // z2_100_0 = z^(2^100 - 1)
  fmul(z2_100_0, t1, z2_50_0);

  // t0 = z^((2^100 - 1) * 2^100)
  fsquare(t1, z2_100_0);
  fsquare(t0, t1);
  for ( j = 2; j < 100; j += 2 )
  {
    fsquare(t1, t0);
    fsquare(t0, t1);
  }
  
  // t1 = z^(2^200 - 1)
  fmul(t1, t0, z2_100_0);
  
  // t1 = z^((2^200 - 1) * 2^50)
  fsquare(t0, t1);
  fsquare(t1, t0);
  for ( j = 2; j < 50; j += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  
  // t0 = z^(2^250 - 1)
  fmul(t0, t1, z2_50_0);
  
  // t1 = z^((2^250 - 1) * 2^5) = z^(2^255 - 32)
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  
  // out = z^(2^255 - 21) = z^(p-2)
  fmul(out, t1, z11);
}