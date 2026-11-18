void plm_video_idct(int *block)

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
  int i_1;
  int i;
  int y7;
  int y6;
  int y5;
  int y4;
  int y3;
  int x4;
  int x3;
  int x2;
  int x1;
  int x0;
  int m0;
  int tmp2;
  int tmp1;
  int b7;
  int b6;
  int b4;
  int b3;
  int b1;
  int *block_local;
  
  for (i = 0; i < 8; i = i + 1) {
    iVar1 = block[i + 0x10] + block[i + 0x30];
    iVar2 = block[i + 8] + block[i + 0x38] + block[i + 0x18] + block[i + 0x28];
    iVar3 = ((block[i + 8] - block[i + 0x38]) * 0x1d9 + (block[i + 0x28] - block[i + 0x18]) * -0xc4
             + 0x80 >> 8) - iVar2;
    iVar4 = iVar3 - (((block[i + 8] + block[i + 0x38]) - (block[i + 0x18] + block[i + 0x28])) *
                     0x16a + 0x80 >> 8);
    iVar5 = block[i] - block[i + 0x20];
    iVar6 = ((block[i + 0x10] - block[i + 0x30]) * 0x16a + 0x80 >> 8) - iVar1;
    iVar7 = block[i] + block[i + 0x20];
    iVar8 = iVar5 + iVar6;
    iVar9 = iVar7 + iVar1;
    iVar5 = iVar5 - iVar6;
    iVar7 = iVar7 - iVar1;
    iVar1 = -((block[i + 0x28] - block[i + 0x18]) * 0x1d9 + (block[i + 8] - block[i + 0x38]) * 0xc4
              + 0x80 >> 8) - iVar4;
    block[i] = iVar2 + iVar9;
    block[i + 8] = iVar3 + iVar8;
    block[i + 0x10] = iVar5 - iVar4;
    block[i + 0x18] = iVar7 - iVar1;
    block[i + 0x20] = iVar7 + iVar1;
    block[i + 0x28] = iVar4 + iVar5;
    block[i + 0x30] = iVar8 - iVar3;
    block[i + 0x38] = iVar9 - iVar2;
  }
  for (i_1 = 0; i_1 < 0x40; i_1 = i_1 + 8) {
    iVar1 = block[i_1 + 2] + block[i_1 + 6];
    iVar2 = block[i_1 + 1] + block[i_1 + 7] + block[i_1 + 3] + block[i_1 + 5];
    iVar3 = ((block[i_1 + 1] - block[i_1 + 7]) * 0x1d9 + (block[i_1 + 5] - block[i_1 + 3]) * -0xc4 +
             0x80 >> 8) - iVar2;
    iVar4 = iVar3 - (((block[i_1 + 1] + block[i_1 + 7]) - (block[i_1 + 3] + block[i_1 + 5])) * 0x16a
                     + 0x80 >> 8);
    iVar5 = block[i_1] - block[i_1 + 4];
    iVar6 = ((block[i_1 + 2] - block[i_1 + 6]) * 0x16a + 0x80 >> 8) - iVar1;
    iVar7 = block[i_1] + block[i_1 + 4];
    iVar8 = iVar5 + iVar6;
    iVar9 = iVar7 + iVar1;
    iVar5 = iVar5 - iVar6;
    iVar7 = iVar7 - iVar1;
    iVar1 = -((block[i_1 + 5] - block[i_1 + 3]) * 0x1d9 + (block[i_1 + 1] - block[i_1 + 7]) * 0xc4 +
              0x80 >> 8) - iVar4;
    block[i_1] = iVar2 + iVar9 + 0x80 >> 8;
    block[i_1 + 1] = iVar3 + iVar8 + 0x80 >> 8;
    block[i_1 + 2] = (iVar5 - iVar4) + 0x80 >> 8;
    block[i_1 + 3] = (iVar7 - iVar1) + 0x80 >> 8;
    block[i_1 + 4] = iVar7 + iVar1 + 0x80 >> 8;
    block[i_1 + 5] = iVar4 + iVar5 + 0x80 >> 8;
    block[i_1 + 6] = (iVar8 - iVar3) + 0x80 >> 8;
    block[i_1 + 7] = (iVar9 - iVar2) + 0x80 >> 8;
  }
  return;
}