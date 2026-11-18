void MurmurHash3_x86_128(void *key,int len,uint32_t seed,void *out)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  int iVar11;
  uint32_t k4;
  uint32_t k3;
  uint32_t k2;
  uint32_t k1;
  uint8_t *tail;
  uint32_t k4_1;
  uint32_t k3_1;
  uint32_t k2_1;
  uint32_t k1_1;
  uint32_t *blocks;
  uint32_t c4;
  uint32_t c3;
  uint32_t c2;
  uint32_t c1;
  uint32_t h4;
  uint32_t h3;
  uint32_t h2;
  uint32_t h1;
  int i;
  int nblocks;
  uint8_t *data;
  void *out_local;
  uint32_t seed_local;
  int len_local;
  void *key_local;
  
  iVar5 = len / 0x10;
  iVar11 = iVar5 << 4;
  h4 = seed;
  h3 = seed;
  h2 = seed;
  h1 = seed;
  for (i = -iVar5; i != 0; i = i + 1) {
    iVar1 = *(int *)((long)key + (long)(i << 2) * 4 + (long)iVar11);
    iVar2 = *(int *)((long)key + (long)(i * 4 + 1) * 4 + (long)iVar11);
    iVar3 = *(int *)((long)key + (long)(i * 4 + 2) * 4 + (long)iVar11);
    iVar4 = *(int *)((long)key + (long)(i * 4 + 3) * 4 + (long)iVar11);
    uVar6 = (iVar1 * -0x34f28000 | (uint)(iVar1 * 0x239b961b) >> 0x11) * -0x54f16877 ^ h1;
    h1 = (h2 + (uVar6 << 0x13 | uVar6 >> 0xd)) * 5 + 0x561ccd1b;
    uVar6 = (iVar2 * -0x68770000 | (uint)(iVar2 * -0x54f16877) >> 0x10) * 0x38b34ae5 ^ h2;
    h2 = (h3 + (uVar6 << 0x11 | uVar6 >> 0xf)) * 5 + 0xbcaa747;
    uVar6 = (iVar3 * -0x6a360000 | (uint)(iVar3 * 0x38b34ae5) >> 0xf) * -0x5e1c746d ^ h3;
    h3 = (h4 + (uVar6 << 0xf | uVar6 >> 0x11)) * 5 + 0x96cd1c35;
    uVar6 = (iVar4 * 0x2e4c0000 | (uint)(iVar4 * -0x5e1c746d) >> 0xe) * 0x239b961b ^ h4;
    h4 = (h1 + (uVar6 << 0xd | uVar6 >> 0x13)) * 5 + 0x32ac3b17;
  }
  pbVar10 = (byte *)((long)key + (long)(iVar5 << 4));
  k1 = 0;
  k2 = 0;
  k3 = 0;
  k4 = 0;
  switch(len & 0xf) {
  case 0xf:
    k4 = (uint)pbVar10[0xe] << 0x10;
  case 0xe:
    k4 = (uint)pbVar10[0xd] << 8 ^ k4;
  case 0xd:
    h4 = ((pbVar10[0xc] ^ k4) * 0x2e4c0000 | (pbVar10[0xc] ^ k4) * -0x5e1c746d >> 0xe) * 0x239b961b
         ^ h4;
  case 0xc:
    k3 = (uint)pbVar10[0xb] << 0x18;
  case 0xb:
    k3 = (uint)pbVar10[10] << 0x10 ^ k3;
  case 10:
    k3 = (uint)pbVar10[9] << 8 ^ k3;
  case 9:
    h3 = ((pbVar10[8] ^ k3) * -0x6a360000 | (pbVar10[8] ^ k3) * 0x38b34ae5 >> 0xf) * -0x5e1c746d ^
         h3;
  case 8:
    k2 = (uint)pbVar10[7] << 0x18;
  case 7:
    k2 = (uint)pbVar10[6] << 0x10 ^ k2;
  case 6:
    k2 = (uint)pbVar10[5] << 8 ^ k2;
  case 5:
    h2 = ((pbVar10[4] ^ k2) * -0x68770000 | (pbVar10[4] ^ k2) * -0x54f16877 >> 0x10) * 0x38b34ae5 ^
         h2;
  case 4:
    k1 = (uint)pbVar10[3] << 0x18;
  case 3:
    k1 = (uint)pbVar10[2] << 0x10 ^ k1;
  case 2:
    k1 = (uint)pbVar10[1] << 8 ^ k1;
  case 1:
    h1 = ((*pbVar10 ^ k1) * -0x34f28000 | (*pbVar10 ^ k1) * 0x239b961b >> 0x11) * -0x54f16877 ^ h1;
  default:
    uVar6 = (len ^ h4) + (len ^ h3) + (len ^ h2) + (len ^ h1);
    uVar7 = uVar6 + (len ^ h2);
    uVar8 = uVar6 + (len ^ h3);
    uVar9 = uVar6 + (len ^ h4);
    uVar6 = (uVar6 >> 0x10 ^ uVar6) * -0x7a143595;
    uVar6 = (uVar6 >> 0xd ^ uVar6) * -0x3d4d51cb;
    uVar7 = (uVar7 >> 0x10 ^ uVar7) * -0x7a143595;
    uVar7 = (uVar7 >> 0xd ^ uVar7) * -0x3d4d51cb;
    uVar7 = uVar7 >> 0x10 ^ uVar7;
    uVar8 = (uVar8 >> 0x10 ^ uVar8) * -0x7a143595;
    uVar8 = (uVar8 >> 0xd ^ uVar8) * -0x3d4d51cb;
    uVar8 = uVar8 >> 0x10 ^ uVar8;
    uVar9 = (uVar9 >> 0x10 ^ uVar9) * -0x7a143595;
    uVar9 = (uVar9 >> 0xd ^ uVar9) * -0x3d4d51cb;
    uVar9 = uVar9 >> 0x10 ^ uVar9;
    iVar5 = uVar9 + uVar8 + uVar7 + (uVar6 >> 0x10 ^ uVar6);
    *(int *)out = iVar5;
    *(uint *)((long)out + 4) = iVar5 + uVar7;
    *(uint *)((long)out + 8) = iVar5 + uVar8;
    *(uint *)((long)out + 0xc) = iVar5 + uVar9;
    return;
  }
}