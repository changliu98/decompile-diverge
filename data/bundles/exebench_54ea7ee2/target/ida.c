void __cdecl BTIC2D_TransWHT_Vert8(int *iblk, int *oblk)
{
  int v2; // eax
  int c4; // [rsp+Ch] [rbp-84h]
  int c2; // [rsp+14h] [rbp-7Ch]
  int c1; // [rsp+18h] [rbp-78h]
  int b7; // [rsp+20h] [rbp-70h]
  int b5; // [rsp+28h] [rbp-68h]
  int b3; // [rsp+30h] [rbp-60h]
  int b1; // [rsp+38h] [rbp-58h]
  int a7; // [rsp+40h] [rbp-50h]
  int a6; // [rsp+44h] [rbp-4Ch]
  int ib7; // [rsp+60h] [rbp-30h]
  int ib6; // [rsp+64h] [rbp-2Ch]
  int ib5; // [rsp+68h] [rbp-28h]
  int ib4; // [rsp+6Ch] [rbp-24h]
  int ib3; // [rsp+70h] [rbp-20h]
  int ib2; // [rsp+74h] [rbp-1Ch]
  int ib1; // [rsp+78h] [rbp-18h]
  int ib0; // [rsp+7Ch] [rbp-14h]

  ib0 = *iblk;
  ib1 = iblk[8];
  ib2 = iblk[16];
  ib3 = iblk[24];
  ib4 = iblk[32];
  ib5 = iblk[40];
  ib6 = iblk[48];
  ib7 = iblk[56];
  a6 = ((ib6 + ib2) >> 1) - ib6;
  a7 = ((ib7 + ib3) >> 1) - ib7;
  b1 = ib7 + ib3 + ib5 + ib1;
  b3 = (b1 >> 1) - (ib7 + ib3);
  b5 = a7 + ((ib5 + ib1) >> 1) - ib5;
  b7 = (b5 >> 1) - a7;
  c1 = ((b1 + ib6 + ib2 + ib4 + *iblk) >> 1) - b1;
  c2 = b3 + ((ib6 + ib2 + ib4 + *iblk) >> 1) - (ib6 + ib2);
  c4 = b5 + a6 + ((ib4 + *iblk) >> 1) - ib4;
  v2 = ((b7 + ((a6 + ((ib4 + *iblk) >> 1) - ib4) >> 1) - a6) >> 1) - b7;
  *oblk = b1 + ib6 + ib2 + ib4 + *iblk;
  oblk[8] = c4;
  oblk[16] = b7 + ((a6 + ((ib4 + ib0) >> 1) - ib4) >> 1) - a6;
  oblk[24] = c2;
  oblk[32] = (c2 >> 1) - b3;
  oblk[40] = v2;
  oblk[48] = (c4 >> 1) - b5;
  oblk[56] = c1;
}