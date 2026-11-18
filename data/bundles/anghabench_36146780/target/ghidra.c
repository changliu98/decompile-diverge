void wmv2_idct_row_mmi(short *b)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int a7;
  int a6;
  int a5;
  int a4;
  int a3;
  int a2;
  int a1;
  int a0;
  int s2;
  int s1;
  short *b_local;
  
  iVar1 = (int)W0 * (int)*b + (int)W0 * (int)b[4];
  iVar2 = (int)W1 * (int)b[1] + (int)W7 * (int)b[7];
  iVar3 = (int)W2 * (int)b[2] + (int)W6 * (int)b[6];
  iVar4 = (int)W3 * (int)b[5] - (int)W5 * (int)b[3];
  iVar5 = (int)W0 * (int)*b - (int)W0 * (int)b[4];
  iVar6 = (int)W5 * (int)b[5] + (int)W3 * (int)b[3];
  iVar7 = (int)W6 * (int)b[2] - (int)W2 * (int)b[6];
  iVar8 = (int)W7 * (int)b[1] - (int)W1 * (int)b[7];
  iVar9 = (((iVar2 - iVar6) + iVar8) - iVar4) * 0xb5 + 0x80 >> 8;
  iVar10 = (((iVar2 - iVar6) - iVar8) + iVar4) * 0xb5 + 0x80 >> 8;
  *b = (short)((uint)(iVar1 + iVar3 + iVar2 + iVar6 + 0x80) >> 8);
  b[1] = (short)((uint)(iVar5 + iVar7 + iVar9 + 0x80) >> 8);
  b[2] = (short)((uint)((iVar5 - iVar7) + iVar10 + 0x80) >> 8);
  b[3] = (short)((uint)((iVar1 - iVar3) + iVar8 + iVar4 + 0x80) >> 8);
  b[4] = (short)((uint)((((iVar1 - iVar3) - iVar8) - iVar4) + 0x80) >> 8);
  b[5] = (short)((uint)(((iVar5 - iVar7) - iVar10) + 0x80) >> 8);
  b[6] = (short)((uint)(((iVar5 + iVar7) - iVar9) + 0x80) >> 8);
  b[7] = (short)((uint)((((iVar1 + iVar3) - iVar2) - iVar6) + 0x80) >> 8);
  return;
}