int mpeg3video_idctrow(short *blk)

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
  
  iVar2 = blk[4] * 0x800;
  iVar6 = (int)blk[6];
  iVar7 = (int)blk[2];
  iVar8 = (int)blk[1];
  iVar9 = (int)blk[7];
  iVar10 = (int)blk[5];
  iVar11 = (int)blk[3];
  bVar12 = (((((iVar2 != 0 || iVar6 != 0) || iVar7 != 0) || iVar8 != 0) || iVar9 != 0) ||
           iVar10 != 0) || iVar11 != 0;
  if (bVar12) {
    iVar3 = *blk * 0x800 + 0x80;
    iVar4 = (iVar8 + iVar9) * 0x235;
    iVar5 = iVar4 + iVar8 * 0x8e4;
    iVar4 = iVar4 + iVar9 * -0xd4e;
    iVar9 = (iVar10 + iVar11) * 0x968;
    iVar8 = iVar9 + iVar10 * -799;
    iVar9 = iVar9 + iVar11 * -0xfb1;
    iVar2 = iVar3 + iVar2;
    iVar3 = iVar3 + blk[4] * -0x800;
    iVar10 = (iVar7 + iVar6) * 0x454;
    iVar6 = iVar10 + iVar6 * -0xec8;
    iVar10 = iVar10 + iVar7 * 0x620;
    iVar7 = iVar5 + iVar8;
    iVar5 = iVar5 - iVar8;
    iVar8 = iVar4 + iVar9;
    iVar4 = iVar4 - iVar9;
    iVar9 = iVar2 + iVar10;
    iVar2 = iVar2 - iVar10;
    iVar10 = iVar3 + iVar6;
    iVar3 = iVar3 - iVar6;
    iVar6 = (iVar5 + iVar4) * 0xb5 + 0x80 >> 8;
    iVar11 = (iVar5 - iVar4) * 0xb5 + 0x80 >> 8;
    *blk = (short)((uint)(iVar9 + iVar7) >> 8);
    blk[1] = (short)((uint)(iVar10 + iVar6) >> 8);
    blk[2] = (short)((uint)(iVar3 + iVar11) >> 8);
    blk[3] = (short)((uint)(iVar2 + iVar8) >> 8);
    blk[4] = (short)((uint)(iVar2 - iVar8) >> 8);
    blk[5] = (short)((uint)(iVar3 - iVar11) >> 8);
    blk[6] = (short)((uint)(iVar10 - iVar6) >> 8);
    blk[7] = (short)((uint)(iVar9 - iVar7) >> 8);
  }
  else {
    sVar1 = *blk << 3;
    blk[7] = sVar1;
    blk[6] = sVar1;
    blk[5] = sVar1;
    blk[4] = sVar1;
    blk[3] = sVar1;
    blk[2] = sVar1;
    blk[1] = sVar1;
    *blk = sVar1;
  }
  local_c = (uint)bVar12;
  return local_c;
}