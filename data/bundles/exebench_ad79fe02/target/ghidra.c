int mpeg3video_idctcol(short *blk)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  int x8;
  int x7;
  int x6;
  int x5;
  int x4;
  int x3;
  int x2;
  int x1;
  int x0;
  short *blk_local;
  uint local_c;
  
  iVar2 = blk[0x20] * 0x100;
  iVar6 = (int)blk[0x30];
  iVar7 = (int)blk[0x10];
  iVar8 = (int)blk[8];
  iVar9 = (int)blk[0x38];
  iVar10 = (int)blk[0x28];
  iVar11 = (int)blk[0x18];
  bVar12 = (((((iVar2 != 0 || iVar6 != 0) || iVar7 != 0) || iVar8 != 0) || iVar9 != 0) ||
           iVar10 != 0) || iVar11 != 0;
  if (bVar12) {
    iVar3 = *blk * 0x100 + 0x2000;
    iVar4 = (iVar8 + iVar9) * 0x235 + 4;
    iVar5 = iVar4 + iVar8 * 0x8e4 >> 3;
    iVar4 = iVar4 + iVar9 * -0xd4e >> 3;
    iVar8 = (iVar10 + iVar11) * 0x968 + 4;
    iVar9 = iVar8 + iVar10 * -799 >> 3;
    iVar8 = iVar8 + iVar11 * -0xfb1 >> 3;
    iVar2 = iVar3 + iVar2;
    iVar3 = iVar3 + blk[0x20] * -0x100;
    iVar10 = (iVar7 + iVar6) * 0x454 + 4;
    iVar6 = iVar10 + iVar6 * -0xec8 >> 3;
    iVar7 = iVar10 + iVar7 * 0x620 >> 3;
    iVar10 = iVar5 + iVar9;
    iVar5 = iVar5 - iVar9;
    iVar9 = iVar4 + iVar8;
    iVar4 = iVar4 - iVar8;
    iVar8 = iVar2 + iVar7;
    iVar2 = iVar2 - iVar7;
    iVar7 = iVar3 + iVar6;
    iVar3 = iVar3 - iVar6;
    iVar6 = (iVar5 + iVar4) * 0xb5 + 0x80 >> 8;
    iVar11 = (iVar5 - iVar4) * 0xb5 + 0x80 >> 8;
    *blk = (short)(iVar8 + iVar10 >> 0xe);
    blk[8] = (short)(iVar7 + iVar6 >> 0xe);
    blk[0x10] = (short)(iVar3 + iVar11 >> 0xe);
    blk[0x18] = (short)(iVar2 + iVar9 >> 0xe);
    blk[0x20] = (short)(iVar2 - iVar9 >> 0xe);
    blk[0x28] = (short)(iVar3 - iVar11 >> 0xe);
    blk[0x30] = (short)(iVar7 - iVar6 >> 0xe);
    blk[0x38] = (short)(iVar8 - iVar10 >> 0xe);
  }
  else {
    sVar1 = (short)(*blk + 0x20 >> 6);
    blk[0x38] = sVar1;
    blk[0x30] = sVar1;
    blk[0x28] = sVar1;
    blk[0x20] = sVar1;
    blk[0x18] = sVar1;
    blk[0x10] = sVar1;
    blk[8] = sVar1;
    *blk = sVar1;
  }
  local_c = (uint)bVar12;
  return local_c;
}