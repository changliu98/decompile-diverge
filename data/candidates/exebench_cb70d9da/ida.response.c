void __cdecl BTIC2D_TransDCT_Vert(int *iblk, int *oblk)
{
  int ib1p6n2n5; // [rsp+0h] [rbp-78h]
  int ib0p7n3n4; // [rsp+4h] [rbp-74h]
  int ob7; // [rsp+28h] [rbp-50h]
  int ob5; // [rsp+30h] [rbp-48h]
  int ob4; // [rsp+34h] [rbp-44h]
  int ob3; // [rsp+38h] [rbp-40h]
  int ob1; // [rsp+40h] [rbp-38h]
  int ib7; // [rsp+48h] [rbp-30h]
  int ib6; // [rsp+4Ch] [rbp-2Ch]
  int ib5; // [rsp+50h] [rbp-28h]
  int ib4; // [rsp+54h] [rbp-24h]
  int ib3; // [rsp+58h] [rbp-20h]
  int ib2; // [rsp+5Ch] [rbp-1Ch]
  int ib1; // [rsp+60h] [rbp-18h]

  ib1 = iblk[8];
  ib2 = iblk[16];
  ib3 = iblk[24];
  ib4 = iblk[32];
  ib5 = iblk[40];
  ib6 = iblk[48];
  ib7 = iblk[56];
  ob4 = 91 * (ib4 + ib3 + ib7 + *iblk - (ib6 + ib1) - (ib5 + ib2));
  ib0p7n3n4 = ib7 + *iblk - (ib4 + ib3);
  ib1p6n2n5 = ib6 + ib1 - (ib5 + ib2);
  ob1 = 25 * (ib3 - ib4) + 71 * (ib2 - ib5) + 106 * (ib1 - ib6) + 126 * (*iblk - ib7);
  ob3 = 106 * (*iblk - ib7) - 25 * (ib1 - ib6) - 126 * (ib2 - ib5) - 71 * (ib3 - ib4);
  ob5 = 106 * (ib3 - ib4) + 25 * (ib2 - ib5) + 71 * (*iblk - ib7) - 126 * (ib1 - ib6);
  ob7 = 106 * (ib2 - ib5) + 25 * (*iblk - ib7) - 71 * (ib1 - ib6) - 126 * (ib3 - ib4);
  *oblk = (91 * (ib4 + ib3 + ib5 + ib2 + ib6 + ib1 + ib7 + *iblk) + 0x8000) >> 16;
  oblk[8] = (ob1 + 0x8000) >> 16;
  oblk[16] = (49 * ib1p6n2n5 + 118 * ib0p7n3n4 + 0x8000) >> 16;
  oblk[24] = (ob3 + 0x8000) >> 16;
  oblk[32] = (ob4 + 0x8000) >> 16;
  oblk[40] = (ob5 + 0x8000) >> 16;
  oblk[48] = (49 * ib0p7n3n4 - 118 * ib1p6n2n5 + 0x8000) >> 16;
  oblk[56] = (ob7 + 0x8000) >> 16;
}