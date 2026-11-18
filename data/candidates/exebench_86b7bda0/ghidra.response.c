void njRowIDCT(int *blk)

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
  int x8;
  int x7;
  int x6;
  int x5;
  int x4;
  int x3;
  int x2;
  int x1;
  int x0;
  int *blk_local;
  
  iVar1 = blk[4] * 0x800;
  iVar10 = blk[6];
  iVar8 = blk[2];
  iVar6 = blk[1];
  iVar5 = blk[7];
  iVar7 = blk[5];
  iVar9 = blk[3];
  if ((((((iVar1 == 0 && iVar10 == 0) && iVar8 == 0) && iVar6 == 0) && iVar5 == 0) && iVar7 == 0) &&
      iVar9 == 0) {
    iVar10 = *blk << 3;
    blk[7] = iVar10;
    blk[6] = iVar10;
    blk[5] = iVar10;
    blk[4] = iVar10;
    blk[3] = iVar10;
    blk[2] = iVar10;
    blk[1] = iVar10;
    *blk = iVar10;
  }
  else {
    iVar2 = *blk * 0x800 + 0x80;
    iVar3 = (iVar6 + iVar5) * 0x235;
    iVar4 = iVar3 + iVar6 * 0x8e4;
    iVar3 = iVar3 + iVar5 * -0xd4e;
    iVar5 = (iVar7 + iVar9) * 0x968;
    iVar6 = iVar5 + iVar7 * -799;
    iVar5 = iVar5 + iVar9 * -0xfb1;
    iVar1 = iVar2 + iVar1;
    iVar2 = iVar2 + blk[4] * -0x800;
    iVar7 = (iVar8 + iVar10) * 0x454;
    iVar10 = iVar7 + iVar10 * -0xec8;
    iVar7 = iVar7 + iVar8 * 0x620;
    iVar8 = iVar4 + iVar6;
    iVar4 = iVar4 - iVar6;
    iVar6 = iVar3 + iVar5;
    iVar3 = iVar3 - iVar5;
    iVar5 = iVar1 + iVar7;
    iVar1 = iVar1 - iVar7;
    iVar7 = iVar2 + iVar10;
    iVar2 = iVar2 - iVar10;
    iVar10 = (iVar4 + iVar3) * 0xb5 + 0x80 >> 8;
    iVar9 = (iVar4 - iVar3) * 0xb5 + 0x80 >> 8;
    *blk = iVar5 + iVar8 >> 8;
    blk[1] = iVar7 + iVar10 >> 8;
    blk[2] = iVar2 + iVar9 >> 8;
    blk[3] = iVar1 + iVar6 >> 8;
    blk[4] = iVar1 - iVar6 >> 8;
    blk[5] = iVar2 - iVar9 >> 8;
    blk[6] = iVar7 - iVar10 >> 8;
    blk[7] = iVar5 - iVar8 >> 8;
  }
  return;
}