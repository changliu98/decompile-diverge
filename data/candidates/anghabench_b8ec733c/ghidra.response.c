void vc1_inv_trans_8x8_c(int16_t *block)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int16_t temp [64];
  int16_t *dst;
  int16_t *src;
  int t8;
  int t7;
  int t6;
  int t5;
  int t4;
  int t3;
  int t2;
  int t1;
  int i;
  int16_t *block_local;
  
  dst = temp;
  src = block;
  for (i = 0; i < 8; i = i + 1) {
    iVar1 = ((int)*src + (int)src[0x20]) * 0xc + 4;
    iVar2 = ((int)*src - (int)src[0x20]) * 0xc + 4;
    iVar3 = src[0x10] * 0x10 + src[0x30] * 6;
    iVar4 = src[0x10] * 6 + src[0x30] * -0x10;
    iVar5 = iVar1 + iVar3;
    iVar6 = iVar2 + iVar4;
    iVar2 = iVar2 - iVar4;
    iVar1 = iVar1 - iVar3;
    iVar3 = src[8] * 0x10 + src[0x18] * 0xf + src[0x28] * 9 + src[0x38] * 4;
    iVar4 = src[8] * 0xf + src[0x18] * -4 + src[0x28] * -0x10 + src[0x38] * -9;
    iVar7 = src[8] * 9 + src[0x18] * -0x10 + src[0x28] * 4 + src[0x38] * 0xf;
    iVar8 = src[8] * 4 + src[0x18] * -9 + src[0x28] * 0xf + src[0x38] * -0x10;
    *dst = (int16_t)(iVar5 + iVar3 >> 3);
    dst[1] = (int16_t)(iVar6 + iVar4 >> 3);
    dst[2] = (int16_t)(iVar2 + iVar7 >> 3);
    dst[3] = (int16_t)(iVar1 + iVar8 >> 3);
    dst[4] = (int16_t)(iVar1 - iVar8 >> 3);
    dst[5] = (int16_t)(iVar2 - iVar7 >> 3);
    dst[6] = (int16_t)(iVar6 - iVar4 >> 3);
    dst[7] = (int16_t)(iVar5 - iVar3 >> 3);
    src = src + 1;
    dst = dst + 8;
  }
  src = temp;
  dst = block;
  for (i = 0; i < 8; i = i + 1) {
    iVar1 = ((int)*src + (int)src[0x20]) * 0xc + 0x40;
    iVar2 = ((int)*src - (int)src[0x20]) * 0xc + 0x40;
    iVar3 = src[0x10] * 0x10 + src[0x30] * 6;
    iVar4 = src[0x10] * 6 + src[0x30] * -0x10;
    iVar5 = iVar1 + iVar3;
    iVar6 = iVar2 + iVar4;
    iVar2 = iVar2 - iVar4;
    iVar1 = iVar1 - iVar3;
    iVar3 = src[8] * 0x10 + src[0x18] * 0xf + src[0x28] * 9 + src[0x38] * 4;
    iVar4 = src[8] * 0xf + src[0x18] * -4 + src[0x28] * -0x10 + src[0x38] * -9;
    iVar7 = src[8] * 9 + src[0x18] * -0x10 + src[0x28] * 4 + src[0x38] * 0xf;
    iVar8 = src[8] * 4 + src[0x18] * -9 + src[0x28] * 0xf + src[0x38] * -0x10;
    *dst = (int16_t)(iVar5 + iVar3 >> 7);
    dst[8] = (int16_t)(iVar6 + iVar4 >> 7);
    dst[0x10] = (int16_t)(iVar2 + iVar7 >> 7);
    dst[0x18] = (int16_t)(iVar1 + iVar8 >> 7);
    dst[0x20] = (int16_t)((iVar1 - iVar8) + 1 >> 7);
    dst[0x28] = (int16_t)((iVar2 - iVar7) + 1 >> 7);
    dst[0x30] = (int16_t)((iVar6 - iVar4) + 1 >> 7);
    dst[0x38] = (int16_t)((iVar5 - iVar3) + 1 >> 7);
    src = src + 1;
    dst = dst + 1;
  }
  return;
}