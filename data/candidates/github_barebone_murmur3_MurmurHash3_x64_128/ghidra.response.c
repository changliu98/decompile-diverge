void MurmurHash3_x64_128(void *key,int len,uint32_t seed,void *out)

{
  ulong uVar1;
  byte *pbVar2;
  ulong uVar3;
  long lVar4;
  uint64_t k2;
  uint64_t k1;
  uint8_t *tail;
  uint64_t k2_1;
  uint64_t k1_1;
  uint64_t *blocks;
  uint64_t c2;
  uint64_t c1;
  uint64_t h2;
  uint64_t h1;
  int i;
  int nblocks;
  uint8_t *data;
  void *out_local;
  uint32_t seed_local;
  int len_local;
  void *key_local;
  
  h1 = (uint64_t)seed;
  h2 = (uint64_t)seed;
  for (i = 0; i < len / 0x10; i = i + 1) {
    lVar4 = *(long *)((long)key + (long)(i << 1) * 8);
    uVar1 = (lVar4 * -0x775ed61580000000 | (ulong)(lVar4 * -0x783c846eeebdac2b) >> 0x21) *
            0x4cf5ad432745937f ^ h1;
    h1 = (h2 + (uVar1 << 0x1b | uVar1 >> 0x25)) * 5 + 0x52dce729;
    uVar1 = *(long *)((long)key + (long)(i * 2 + 1) * 8) * 0x4cf5ad432745937f;
    uVar1 = (uVar1 << 0x21 | uVar1 >> 0x1f) * -0x783c846eeebdac2b ^ h2;
    h2 = (h1 + (uVar1 << 0x1f | uVar1 >> 0x21)) * 5 + 0x38495ab5;
  }
  pbVar2 = (byte *)((long)key + (long)(len / 0x10 << 4));
  k1 = 0;
  k2 = 0;
  switch(len & 0xf) {
  case 0xf:
    k2 = (ulong)pbVar2[0xe] << 0x30;
  case 0xe:
    k2 = (ulong)pbVar2[0xd] << 0x28 ^ k2;
  case 0xd:
    k2 = (ulong)pbVar2[0xc] << 0x20 ^ k2;
  case 0xc:
    k2 = (ulong)pbVar2[0xb] << 0x18 ^ k2;
  case 0xb:
    k2 = (ulong)pbVar2[10] << 0x10 ^ k2;
  case 10:
    k2 = (ulong)pbVar2[9] << 8 ^ k2;
  case 9:
    uVar1 = (pbVar2[8] ^ k2) * 0x4cf5ad432745937f;
    h2 = (uVar1 << 0x21 | uVar1 >> 0x1f) * -0x783c846eeebdac2b ^ h2;
  case 8:
    k1 = (ulong)pbVar2[7] << 0x38;
  case 7:
    k1 = (ulong)pbVar2[6] << 0x30 ^ k1;
  case 6:
    k1 = (ulong)pbVar2[5] << 0x28 ^ k1;
  case 5:
    k1 = (ulong)pbVar2[4] << 0x20 ^ k1;
  case 4:
    k1 = (ulong)pbVar2[3] << 0x18 ^ k1;
  case 3:
    k1 = (ulong)pbVar2[2] << 0x10 ^ k1;
  case 2:
    k1 = (ulong)pbVar2[1] << 8 ^ k1;
  case 1:
    h1 = ((*pbVar2 ^ k1) * -0x775ed61580000000 | (*pbVar2 ^ k1) * -0x783c846eeebdac2b >> 0x21) *
         0x4cf5ad432745937f ^ h1;
  default:
    uVar1 = ((long)len ^ h2) + ((long)len ^ h1);
    uVar3 = uVar1 + ((long)len ^ h2);
    uVar1 = (uVar1 >> 0x21 ^ uVar1) * -0xae502812aa7333;
    uVar1 = (uVar1 >> 0x21 ^ uVar1) * -0x3b314601e57a13ad;
    uVar3 = (uVar3 >> 0x21 ^ uVar3) * -0xae502812aa7333;
    uVar3 = (uVar3 >> 0x21 ^ uVar3) * -0x3b314601e57a13ad;
    uVar3 = uVar3 >> 0x21 ^ uVar3;
    lVar4 = uVar3 + (uVar1 >> 0x21 ^ uVar1);
    *(long *)out = lVar4;
    *(ulong *)((long)out + 8) = lVar4 + uVar3;
    return;
  }
}