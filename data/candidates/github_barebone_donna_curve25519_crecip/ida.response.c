void __cdecl crecip(limb *out, const limb *z)
{
  int i; // [rsp+Ch] [rbp-334h]
  int ia; // [rsp+Ch] [rbp-334h]
  int ib; // [rsp+Ch] [rbp-334h]
  int ic; // [rsp+Ch] [rbp-334h]
  int id; // [rsp+Ch] [rbp-334h]
  int ie; // [rsp+Ch] [rbp-334h]
  limb t1[10]; // [rsp+10h] [rbp-330h] BYREF
  limb t0[10]; // [rsp+60h] [rbp-2E0h] BYREF
  limb z2_100_0[10]; // [rsp+B0h] [rbp-290h] BYREF
  limb z2_50_0[10]; // [rsp+100h] [rbp-240h] BYREF
  limb z2_20_0[10]; // [rsp+150h] [rbp-1F0h] BYREF
  limb z2_10_0[10]; // [rsp+1A0h] [rbp-1A0h] BYREF
  limb z2_5_0[10]; // [rsp+1F0h] [rbp-150h] BYREF
  limb z11[10]; // [rsp+240h] [rbp-100h] BYREF
  limb z9[10]; // [rsp+290h] [rbp-B0h] BYREF
  limb z2[10]; // [rsp+2E0h] [rbp-60h] BYREF
  const limb *za; // [rsp+330h] [rbp-10h]
  limb *outa; // [rsp+338h] [rbp-8h]

  outa = out;
  za = z;
  fsquare(z2, z);
  fsquare(t1, z2);
  fsquare(t0, t1);
  fmul(z9, t0, za);
  fmul(z11, z9, z2);
  fsquare(t0, z11);
  fmul(z2_5_0, t0, z9);
  fsquare(t0, z2_5_0);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fmul(z2_10_0, t0, z2_5_0);
  fsquare(t0, z2_10_0);
  fsquare(t1, t0);
  for ( i = 2; i < 10; i += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  fmul(z2_20_0, t1, z2_10_0);
  fsquare(t0, z2_20_0);
  fsquare(t1, t0);
  for ( ia = 2; ia < 20; ia += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  fmul(t0, t1, z2_20_0);
  fsquare(t1, t0);
  fsquare(t0, t1);
  for ( ib = 2; ib < 10; ib += 2 )
  {
    fsquare(t1, t0);
    fsquare(t0, t1);
  }
  fmul(z2_50_0, t0, z2_10_0);
  fsquare(t0, z2_50_0);
  fsquare(t1, t0);
  for ( ic = 2; ic < 50; ic += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  fmul(z2_100_0, t1, z2_50_0);
  fsquare(t1, z2_100_0);
  fsquare(t0, t1);
  for ( id = 2; id < 100; id += 2 )
  {
    fsquare(t1, t0);
    fsquare(t0, t1);
  }
  fmul(t1, t0, z2_100_0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  for ( ie = 2; ie < 50; ie += 2 )
  {
    fsquare(t0, t1);
    fsquare(t1, t0);
  }
  fmul(t0, t1, z2_50_0);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  fsquare(t0, t1);
  fsquare(t1, t0);
  fmul(outa, t1, z11);
}