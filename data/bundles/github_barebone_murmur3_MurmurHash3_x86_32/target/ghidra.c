void MurmurHash3_x86_32(void *key,int len,uint32_t seed,void *out)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  uint32_t k1;
  uint8_t *tail;
  uint32_t k1_1;
  uint32_t *blocks;
  uint32_t c2;
  uint32_t c1;
  uint32_t h1;
  int i;
  int nblocks;
  uint8_t *data;
  void *out_local;
  uint32_t seed_local;
  int len_local;
  void *key_local;
  
  iVar2 = len / 4;
  h1 = seed;
  for (i = -iVar2; i != 0; i = i + 1) {
    iVar1 = *(int *)((long)key + (long)i * 4 + (long)(iVar2 << 2));
    uVar3 = (iVar1 * 0x16a88000 | (uint)(iVar1 * -0x3361d2af) >> 0x11) * 0x1b873593 ^ h1;
    h1 = (uVar3 << 0xd | uVar3 >> 0x13) * 5 + 0xe6546b64;
  }
  pbVar4 = (byte *)((long)key + (long)(iVar2 << 2));
  k1 = 0;
  uVar3 = len & 3;
  if (uVar3 != 1) {
    if (uVar3 != 2) {
      if (uVar3 != 3) goto LAB_00101395;
      k1 = (uint)pbVar4[2] << 0x10;
    }
    k1 = (uint)pbVar4[1] << 8 ^ k1;
  }
  h1 = ((*pbVar4 ^ k1) * 0x16a88000 | (*pbVar4 ^ k1) * -0x3361d2af >> 0x11) * 0x1b873593 ^ h1;
LAB_00101395:
  uVar3 = ((len ^ h1) >> 0x10 ^ len ^ h1) * -0x7a143595;
  uVar3 = (uVar3 >> 0xd ^ uVar3) * -0x3d4d51cb;
  *(uint *)out = uVar3 >> 0x10 ^ uVar3;
  return;
}